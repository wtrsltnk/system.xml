#include "XmlLoader.h"
#include <XmlUnexpectedClosingTagException.h>
#include <XmlUnexpectedEndOfFileException.h>
#include <XmlUndefinedNamespaceFoundException.h>
#include <cstring>

using namespace System::Xml;

XmlLoader::XmlLoader()
{ }

XmlLoader::~XmlLoader()
{ }

#define xmlPrefixNamespace "http://www.w3.org/XML/1998/namespace"
#define xmlnsPrefixNamespace "http://www.w3.org/2000/xmlns/"

void XmlLoader::ResetNamespaces()
{
    this->_currentDefaultNamespace = "";
    this->_namespaces.clear();
    this->_namespaces.insert(std::make_pair("xml", xmlPrefixNamespace));
    this->_namespaces.insert(std::make_pair("xmlns", xmlnsPrefixNamespace));
}

void XmlLoader::Load(XmlDocument& doc, std::istream& fr)
{
    this->ResetNamespaces();

    std::string data((std::istreambuf_iterator<char>(fr)), std::istreambuf_iterator<char>());

    const char* ptr = data.c_str();
    std::string text, str;

    XmlNode* currentNode = &doc;
    try
    {
        while (ptr[0] != '\0')
        {
            // First we save the text as a textnode when a tag is coming up
            if (ptr[0] == '<' && text != "")
            {
                XmlText* node = doc.CreateTextNode();
                node->SetValue(text);
                currentNode->AppendChild(node);

                // Reset the text
                text = "";
            }

            // Now parse any possible tag
            if (this->ParseTag(ptr, "<!--", "-->", str))
            {
                XmlComment* node = doc.CreateComment();
                node->SetValue(str);
                currentNode->AppendChild(node);
            }
            else if (this->ParseTag(ptr, "<![CDATA[", "]]>", str))
            {
                XmlCDataSection* node = doc.CreateCDataSection();
                node->SetValue(str);
                currentNode->AppendChild(node);
            }
            else if (this->ParseTag(ptr, "<!DOCTYPE", ">", str))
            {
                std::string name, publicId, systemId, internalSubset;

                if (str.length() > 0)
                {
                    std::string::size_type found = str.find_first_of(' ');
                    if (found != std::string::npos)
                    {
                        name = str.substr(0, found);
                        str = str.substr(found + 1);
                    }
                }

                // TODO : make sure the correct values are parsed here
                XmlDocumentType* node = doc.CreateDocumentType(name, publicId, systemId, internalSubset);
                currentNode->AppendChild(node);
            }
            else if (this->ParseTag(ptr, "<?", "?>", str))
            {
                std::string::size_type firstSpace = str.find_first_of(" ?");
                std::string target = "xml";
                if (firstSpace != std::string::npos)
                    target = str.substr(0, firstSpace);

                // Parse the attributes
                XmlAttributeCollection attrs;
                this->ParseAttributes(str, doc, attrs);

                XmlProcessingInstruction* node = doc.CreateProcessingInstruction(target, "");
                node->SetAttributes(attrs);
                currentNode->AppendChild(node);
            }
            else if (this->ParseTag(ptr, "</", ">", str))
            {
                std::string prefix, localName;
                this->ParseTagName(str, prefix, localName);

                if (prefix != currentNode->Prefix() && localName == currentNode->LocalName())
                    throw XmlUnexpectedClosingTagException();

                currentNode = currentNode->ParentNode();
            }
            else if (this->ParseTag(ptr, "<", ">", str))
            {
                // Parse Prefix and LocalName from the tag
                std::string prefix, localName;
                this->ParseTagName(str, prefix, localName);

                // Parse the attributes
                XmlAttributeCollection attrs;
                this->ParseAttributes(str, doc, attrs);

                // Determine the NamespaceURI based on prefix, or grab the default namespace
                // Must be down after attribute parsing, or namespaces in attributes are not considered
                std::string namespaceURI = this->ParseNamespaceURI(prefix);

                XmlElement* node = doc.CreateElement(prefix, localName, namespaceURI);
                node->SetAttributes(attrs);
                currentNode->AppendChild(node);

                if (str[str.size()-1] == '/')
                    str = str.substr(0, str.size()-1);
                else
                    currentNode = node;
            }
            else
            {
                text += ptr[0];
                ptr++;
            }
        }
    }
    catch (const XmlException& ex)
    {
        // TODO : clean up the nodes loaded this far
        throw ex;
    }
}

bool XmlLoader::ParseTag(const char*& ptr, const char* open, const char* close, std::string& output)
{
    int openLength = std::string(open).length();
    int closeLength = std::string(close).length();

    if (std::strncmp(ptr, open, openLength) != 0)
        return false;

    ptr += openLength; // skip the open part of tag
    const char* start = ptr;

    while (std::strncmp(ptr, close, closeLength) != 0)
        if ((++ptr)[0] == '\0')
            throw XmlUnexpectedEndOfFileException();

    const char* end = ptr;
    ptr += closeLength;   // skip close part of tag

    output = std::string(start).substr(0, end-start);

    return true;
}

void XmlLoader::ParseTagName(const std::string& str, std::string& prefix, std::string& localName)
{
    localName = str.substr(0, str.find_first_of(" />"));
    std::string::size_type colon = localName.find_first_of(':');
    std::string::size_type space = localName.find_first_of(" />");
    if (colon != std::string::npos && colon < space)
    {
        prefix = localName.substr(0, colon);
        localName = localName.substr(colon + 1, space - (colon + 1));
    }
}

void XmlLoader::ParseAttributes(const std::string& str, XmlDocument& doc, XmlAttributeCollection& attrs)
{
    std::string::size_type firstSpace = str.find_first_of(' ');
    std::string tmp = str;
    std::string::size_type equal, quot1, quot2;
    std::string prefix, localName, namespaceURI;
    while (firstSpace != std::string::npos)
    {
        tmp = tmp.substr(firstSpace + 1);
        equal = tmp.find_first_of('=');
        this->ParseTagName(tmp.substr(0, equal), prefix, localName);

        namespaceURI = this->ParseNamespaceURI(prefix);

        XmlAttribute* attr = doc.CreateAttribute(prefix, localName, namespaceURI);
        attrs.Append(attr);

        quot1 = tmp.find_first_of('\"')+1;
        quot2 = tmp.find_first_of('\"', quot1);
        attr->SetValue(tmp.substr(quot1, quot2 - quot1));

        firstSpace = tmp.find_first_of(' ');

        if (localName == "xmlns")
            this->_currentDefaultNamespace = attr->Value();
        else if (prefix == "xmlns")
        {
            std::map<std::string, std::string>::iterator found = this->_namespaces.find(localName);
            if (found == this->_namespaces.end())
                this->_namespaces.insert(std::make_pair(localName, attr->Value()));
            else
                found->second = attr->Value();
        }
    }
}

std::string XmlLoader::ParseNamespaceURI(const std::string& prefix)
{
    if (prefix != "")
    {
        std::map<std::string, std::string>::iterator found = this->_namespaces.find(prefix);
        if (found != this->_namespaces.end())
            return found->second;
        else
            throw XmlUndefinedNamespaceFoundException(prefix);
    }
    return this->_currentDefaultNamespace;
}