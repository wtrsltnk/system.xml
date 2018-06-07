#include "XmlLoader.h"
#include <algorithm>
#include <cstring>
#include <locale>
#include <xml/XmlUndefinedNamespaceFoundException.h>
#include <xml/XmlUnexpectedClosingTagException.h>
#include <xml/XmlUnexpectedEndOfFileException.h>

using namespace System::Xml;

XmlLoader::XmlLoader()
{
}

XmlLoader::~XmlLoader()
{
}

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

    char const* ptr = data.c_str();
    std::string text, str;

    XmlNode* currentNode = &doc;
    try {
        while (ptr[0] != '\0') {
            // First we save the text as a textnode when a tag is coming up
            if (ptr[0] == '<' && text != "") {
                XmlText* node = doc.CreateTextNode();
                node->SetValue(text);
                currentNode->AppendChild(node);

                // Reset the text
                text = "";
            }

            // Now parse any possible tag
            if (this->ParseTag(ptr, "<!--", "-->", str)) {
                XmlComment* node = doc.CreateComment();
                node->SetValue(str);
                currentNode->AppendChild(node);
            } else if (this->ParseTag(ptr, "<![CDATA[", "]]>", str)) {
                XmlCDataSection* node = doc.CreateCDataSection();
                node->SetValue(str);
                currentNode->AppendChild(node);
            } else if (this->ParseTag(ptr, "<!DOCTYPE", ">", str)) {
                std::string name, publicId, systemId, internalSubset;

                if (str.length() > 0) {
                    std::string::size_type found = str.find_first_of(' ');
                    if (found != std::string::npos) {
                        name = str.substr(0, found);
                        str = str.substr(found + 1);
                    }
                }

                // TODO : make sure the correct values are parsed here
                XmlDocumentType* node = doc.CreateDocumentType(name, publicId, systemId, internalSubset);
                currentNode->AppendChild(node);
            } else if (this->ParseTag(ptr, "<?", "?>", str)) {
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
            } else if (this->ParseTag(ptr, "</", ">", str)) {
                std::string prefix, localName;
                this->ParseTagName(str, prefix, localName);

                if (prefix != currentNode->Prefix() && localName == currentNode->LocalName())
                    throw XmlUnexpectedClosingTagException();

                currentNode = currentNode->ParentNode();
            } else if (this->ParseTag(ptr, "<", ">", str)) {
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

                if (str[str.size() - 1] == '/')
                    str = str.substr(0, str.size() - 1);
                else
                    currentNode = node;
            } else {
                text += ptr[0];
                ptr++;
            }
        }
    } catch (const XmlException& ex) {
        // TODO : clean up the nodes loaded this far
        throw ex;
    }
}

std::string moveToNextUnescapedDoubleQuote(char const*& ptr)
{
    std::string result;
    bool escape = false;

    do {
        result += ptr[0];
        ptr++;
        if (escape && ptr[0] == '\"') {
            escape = false;
            result += ptr[0];
            ptr++;
            continue;
        }
        if (ptr[0] == '\\') {
            escape = true;
        }
    } while (ptr[0] != '\"' && ptr[0] != '\0');

    return result;
}

bool XmlLoader::ParseTag(char const*& ptr, char const* open, char const* close, std::string& output)
{
    int openLength = std::string(open).length();
    int closeLength = std::string(close).length();

    if (std::strncmp(ptr, open, openLength) != 0)
        return false;

    ptr += openLength; // skip the open part of tag
    char const* start = ptr;

    while (std::strncmp(ptr, close, closeLength) != 0) {
        auto c = (++ptr)[0];
        if (c == '\0') {
            throw XmlUnexpectedEndOfFileException();
        }
        if (c == '\"') {
            moveToNextUnescapedDoubleQuote(ptr);
        }
    }

    char const* end = ptr;
    ptr += closeLength; // skip close part of tag

    output = std::string(start).substr(0, end - start);

    return true;
}

void XmlLoader::ParseTagName(std::string& str, std::string& prefix, std::string& localName)
{
    localName = str.substr(0, str.find_first_of(" />"));
    std::string::size_type colon = localName.find_first_of(':');
    std::string::size_type space = localName.find_first_of(" />");
    if (colon != std::string::npos && colon < space) {
        prefix = localName.substr(0, colon);
        localName = localName.substr(colon + 1, space - (colon + 1));
    }
}

std::string getUntilSeperator(char const* ptr, char c)
{
    std::string key;
    do {
        if (ptr[0] == '=') {
            break;
        }
        if (c == '\"') {
            key += moveToNextUnescapedDoubleQuote(ptr);
        } else {
            key += ptr[0];
            ptr++;
        }
    } while (ptr[0] != '\0');

    return key;
}
void XmlLoader::ParseAttributes(std::string& str, XmlDocument& doc, XmlAttributeCollection& attrs)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !std::isspace(ch);
    }));

    auto ptr = str.data();
    std::string key = getUntilSeperator(ptr, '=');
    std::string namespaceURI, prefix;

    while (key != "") {
        ptr++;
        std::string value = getUntilSeperator(ptr, '=');
        if (value != "")
        {
            auto colon = key.find_first_of(':');
            if (colon != std::string::npos)
            {
                prefix = key.substr(0, colon);
                namespaceURI = this->ParseNamespaceURI(prefix);
                key = key.substr(colon + 1);
            }
            XmlAttribute* attr = doc.CreateAttribute(prefix, key, namespaceURI);
            attr->SetValue(value);
            attrs.Append(attr);
        }
    }

    //    std::string::size_type firstSpace = str.find_first_of(' ');
    //    std::string tmp = str;
    //    std::string::size_type equal, quot1, quot2;
    //    std::string prefix, localName, namespaceURI;
    //    while (firstSpace != std::string::npos)
    //    {
    //        tmp = tmp.substr(firstSpace + 1);
    //        equal = tmp.find_first_of('=');
    //        this->ParseTagName(tmp.substr(0, equal), prefix, localName);

    //        namespaceURI = this->ParseNamespaceURI(prefix);

    //        XmlAttribute* attr = doc.CreateAttribute(prefix, localName, namespaceURI);
    //        attrs.Append(attr);

    //        quot1 = tmp.find_first_of('\"')+1;
    //        quot2 = tmp.find_first_of('\"', quot1);
    //        attr->SetValue(tmp.substr(quot1, quot2 - quot1));

    //        firstSpace = tmp.find_first_of(' ');

    //        if (localName == "xmlns")
    //        {
    //            this->_currentDefaultNamespace = attr->Value();
    //        }
    //        else if (prefix == "xmlns")
    //        {
    //            std::map<std::string, std::string>::iterator found = this->_namespaces.find(localName);
    //            if (found == this->_namespaces.end())
    //                this->_namespaces.insert(std::make_pair(localName, attr->Value()));
    //            else
    //                found->second = attr->Value();
    //        }
    //    }
}

std::string XmlLoader::ParseNamespaceURI(const std::string& prefix)
{
    if (prefix != "") {
        std::map<std::string, std::string>::iterator found = this->_namespaces.find(prefix);
        if (found != this->_namespaces.end())
            return found->second;
        else
            throw XmlUndefinedNamespaceFoundException(prefix);
    }
    return this->_currentDefaultNamespace;
}
