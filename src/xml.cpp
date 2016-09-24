#include "xml.h"
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace xml;

/*
 * XmlNodeList
 */
XmlNodeList::XmlNodeList()
{ }

XmlNodeList::XmlNodeList(XmlNode* node)
{
    XmlNode* itr = node->FirstChild();

    if (itr != 0)
    {
        do
        {
            this->push_back(itr);
            itr = itr->NextSibling();
        }
        while (itr != 0 && itr != node->FirstChild());
    }
}

XmlNodeList::~XmlNodeList()
{ }

int XmlNodeList::Count()
{
    return int(this->size());
}

XmlNode* XmlNodeList::operator [](int index)
{
    return this->Item(index);
}

XmlNode* XmlNodeList::Item(int index)
{
    if (index >= 0 && index < this->Count())
        return this->at(index);

    return 0;
}





/*
 * XmlAttributeCollection
 */
XmlAttributeCollection::XmlAttributeCollection()
{ }

XmlAttributeCollection::~XmlAttributeCollection()
{ }

int XmlAttributeCollection::Count()
{
    return int(this->size());
}

XmlAttribute* XmlAttributeCollection::operator [](const std::string& key)
{
    return this->Item(key);
}

XmlAttribute* XmlAttributeCollection::operator [](int index)
{
    return this->ItemAt(index);
}

XmlAttribute* XmlAttributeCollection::Append(XmlAttribute* node)
{
    this->insert(std::make_pair(node->Name(), node));
    return node;
}

XmlAttribute* XmlAttributeCollection::Item(const std::string& key)
{
    if (this->find(key) != this->end())
        return this->at(key);

    return 0;
}

XmlAttribute* XmlAttributeCollection::ItemAt(int index)
{
    XmlAttributeCollection::iterator itr = this->begin();

    for (int i = 0; i < index; i++, ++itr)
        ;

    return itr->second;
}

void XmlAttributeCollection::RemoveAll()
{
    std::map<std::string, XmlAttribute*>::iterator itr = this->begin();
    while (itr !=  this->end())
    {
        delete itr->second;
        this->erase(itr++);
    }
}

void XmlAttributeCollection::RemoveNamedItem(const std::string& name)
{ }

void XmlAttributeCollection::RemoveNamedItem(const std::string& localName, const std::string& namespaceURI)
{ }





/*
 * XmlName
 */
XmlName::XmlName(const std::string& prefix, const std::string& localName, const std::string& ns, XmlDocument* ownerDocument)
    : _prefix(prefix), _localName(localName), _ns(ns), _ownerDocument(ownerDocument)
{
    if (this->_prefix != "")
        this->_name = this->_prefix + ":" + this->_localName;
    else
        this->_name = this->_localName;
}

XmlName::~XmlName()
{ }

const std::string& XmlName::LocalName() const
{
    return this->_localName;
}

const std::string& XmlName::Name() const
{
    return this->_name;
}

const std::string& XmlName::NamespaceURI() const
{
    return this->_ns;
}

XmlDocument* XmlName::OwnerDocument()
{
    return this->_ownerDocument;
}

const std::string& XmlName::Prefix() const
{
    return this->_prefix;
}





/*
 * XmlNode
 */
XmlNode::XmlNode(XmlDocument* doc)
    : _parentNode(doc), _lastNode(0)
{ }

XmlNode::~XmlNode()
{
    this->Attributes().RemoveAll();
    this->RemoveAll();
}

XmlAttributeCollection& XmlNode::Attributes()
{
    return this->_attributes;
}

void XmlNode::SetAttributes(const XmlAttributeCollection& attrs)
{
    this->_attributes = attrs;
}

XmlNodeList XmlNode::ChildNodes()
{
    return XmlNodeList(this);
}

XmlNode* XmlNode::FirstChild()
{
    XmlLinkedNode* lastNode = this->_lastNode;

    if (lastNode != 0 && lastNode != this)
        return lastNode->_next;

    return 0;
}

bool XmlNode::HasChildNodes()
{
    return this->_lastNode != 0;
}

XmlNode* XmlNode::PreviousSibling()
{
    return 0;
}

std::string XmlNode::InnerText()
{
    std::stringstream result;

    for (int i = 0; i < this->ChildNodes().Count(); i++)
        result << this->ChildNodes()[i]->InnerText();

    return result.str();
}

void XmlNode::SetInnerText(const std::string& innerText)
{
    XmlNode* firstChild = this->FirstChild();

    if (firstChild != 0
            && firstChild->NextSibling() != 0
            && firstChild->NodeType() == XmlNodeType::Text)
    {
        firstChild->SetValue(innerText);
    }
    else
    {
        this->RemoveAll();
        this->AppendChild(this->OwnerDocument()->CreateTextNode(innerText));
    }
}

XmlNode* XmlNode::LastChild()
{
    return this->_lastNode;
}

std::string XmlNode::InnerXml()
{
    std::stringstream result;

    for (int i = 0; i < this->ChildNodes().Count(); i++)
        result << this->ChildNodes()[i]->OuterXml();

    return result.str();
}

void XmlNode::SetInnerXml(const std::string& /*innerXml*/)
{ }

XmlNode* XmlNode::NextSibling()
{
    return 0;
}

std::string XmlNode::OuterXml()
{
    std::stringstream result;

    result << "<" << this->Name();

    XmlAttributeCollection::iterator i = this->Attributes().begin();
    for (; i != this->Attributes().end(); ++i)
        result << " " << i->second->Name() << "=\"" << i->second->Value() << "\"";

    result << ">" << this->InnerXml() << "</" << this->Name() << ">";

    return result.str();
}

XmlDocument* XmlNode::OwnerDocument()
{
    if (this->_parentNode->NodeType() == XmlNodeType::Document)
        return (XmlDocument*)this->_parentNode;

    return this->_parentNode->OwnerDocument();
}

XmlNode* XmlNode::ParentNode()
{
    return this->_parentNode;
}

std::string XmlNode::Value()
{
    return "";
}

void XmlNode::SetValue(const std::string& value)
{ }

void XmlNode::AppendChild(XmlNode* child)
{
    child->_parentNode = this;
    XmlLinkedNode* linked = reinterpret_cast<XmlLinkedNode*>(child);
    if (linked != 0)
    {
        if (this->_lastNode != 0)
        {
            linked->_next = this->_lastNode->_next;
            this->_lastNode->_next = linked;
        }
        else
            linked->_next = linked;

        this->_lastNode = linked;
    }
}

void XmlNode::RemoveAll()
{
    XmlNode* ptr = this->FirstChild();
    while (ptr != 0)
    {
        XmlNode* tmp = ptr->NextSibling();
        this->RemoveChild(ptr);
        delete ptr;
        ptr = tmp;
    }
}

XmlNode* XmlNode::RemoveChild(XmlNode* child)
{
    if (child->_parentNode != this)
        throw XmlException("Argument exception, given child is no child of mine!");

    XmlLinkedNode* childNode = (XmlLinkedNode*)child;
    XmlLinkedNode* prevNode = (XmlLinkedNode*)child->PreviousSibling();
    XmlLinkedNode* nextNode = childNode->_next;

    prevNode->_next = nextNode;
    childNode->_next = 0;
    childNode->_parentNode = 0;

    return childNode;
}

XmlNode* XmlNode::FindChild(XmlNodeType::Type type)
{
    XmlNode* find = this->FirstChild();

    while (find != 0)
    {
        if (find->NodeType() == type)
            return find;
        find = find->NextSibling();
    }

    return 0;
}

void XmlNode::SetParent(XmlNode* parent)
{
    if (parent == 0)
        this->_parentNode = this->OwnerDocument();
    else
        this->_parentNode = parent;
}





/*
 * XmlAttribute
 */
XmlAttribute::XmlAttribute(XmlDocument* ownerDocument, const std::string& name)
    : XmlNode(ownerDocument), _name(XmlName("", name, "", ownerDocument))
{ }

XmlAttribute::XmlAttribute(XmlDocument* ownerDocument, const std::string& prefix, const std::string& localName, const std::string& ns)
    : XmlNode(ownerDocument), _name(XmlName(prefix, localName, ns, ownerDocument))
{ }

XmlAttribute::~XmlAttribute()
{ }

const std::string& XmlAttribute::LocalName() const
{
    return this->_name.LocalName();
}

const std::string& XmlAttribute::Name() const
{
    return this->_name.Name();
}

const std::string& XmlAttribute::NamespaceURI() const
{
    return this->_name.NamespaceURI();
}

const std::string& XmlAttribute::Prefix() const
{
    return this->_name.Prefix();
}

void XmlAttribute::SetPrefix(const std::string& prefix)
{
    this->_name = this->_name.OwnerDocument()->AddXmlName(prefix, this->LocalName(), this->NamespaceURI());
}

const XmlName& XmlAttribute::XmlNameProp() const
{
    return this->_name;
}

std::string XmlAttribute::Value()
{
    return this->InnerText();
}

void XmlAttribute::SetValue(const std::string& value)
{
    this->SetInnerText(value);
}





/*
 * XmlLinkedNode
 */
XmlLinkedNode::XmlLinkedNode(XmlDocument* ownerDocument)
    : XmlNode(ownerDocument), _next(0)
{ }

XmlLinkedNode::~XmlLinkedNode()
{ }

XmlNode* XmlLinkedNode::PreviousSibling()
{
    XmlNode* parent = this->ParentNode();
    if (parent != 0)
    {
        XmlNode* node = parent->FirstChild();
        while (node != 0)
        {
            XmlNode* nextSibling = node->NextSibling();
            if (nextSibling == this || nextSibling == 0)
                break;
            node = nextSibling;
        }
        return node;
    }
    return 0;
}

XmlNode* XmlLinkedNode::NextSibling()
{
    XmlNode* parent = this->ParentNode();
    if (parent != 0)
    {
        if (this != parent->LastChild())
            return this->_next;
    }
    return 0;
}





/*
 * XmlProcessingInstruction
 */
XmlProcessingInstruction::XmlProcessingInstruction(const std::string& target, const std::string& data, XmlDocument* ownerDocument)
    : XmlLinkedNode(ownerDocument), _target(target), _data(data)
{ }

XmlProcessingInstruction::~XmlProcessingInstruction()
{ }

const std::string& XmlProcessingInstruction::Data() const
{
    return this->_data;
}

void XmlProcessingInstruction::SetData(const std::string& data)
{
    this->_data = data;
}

std::string XmlProcessingInstruction::InnerText()
{
    return this->_data;
}

void XmlProcessingInstruction::SetInnerText(const std::string& innerText)
{
    this->_data = innerText;
}

const std::string& XmlProcessingInstruction::LocalName() const
{
    return this->Name();
}

const std::string& XmlProcessingInstruction::Name() const
{
    return this->_target;
}

const std::string& XmlProcessingInstruction::Target() const
{
    return this->_target;
}

const std::string& XmlProcessingInstruction::NamespaceURI() const
{
    static std::string XmlProcessingInstructionNamespaaceURI = "";

    return XmlProcessingInstructionNamespaaceURI;
}

void XmlProcessingInstruction::SetNamespaceURI(const std::string& namespaceURI)
{ }

std::string XmlProcessingInstruction::Value()
{
    return this->_data;
}

void XmlProcessingInstruction::SetValue(const std::string& value)
{
    this->_data = value;
}

const std::string& XmlProcessingInstruction::Prefix() const
{
    static std::string XmlProcessingInstructionPrefix = "";

    return XmlProcessingInstructionPrefix;
}

void XmlProcessingInstruction::SetPrefix(const std::string& prefix)
{ }





/*
 * XmlElement
 */
XmlElement::XmlElement(XmlDocument* ownerDocument, const std::string& name)
    : XmlLinkedNode(ownerDocument), _name(XmlName("", name, "", ownerDocument))
{ }

XmlElement::XmlElement(XmlDocument* ownerDocument, const std::string& prefix, const std::string& localName, const std::string& ns)
    : XmlLinkedNode(ownerDocument), _name(XmlName(prefix, localName, ns, ownerDocument))
{ }

XmlElement::~XmlElement()
{ }

const std::string& XmlElement::LocalName() const
{
    return this->_name.LocalName();
}

const std::string& XmlElement::Name() const
{
    return this->_name.Name();
}

const std::string& XmlElement::NamespaceURI() const
{
    return this->_name.NamespaceURI();
}

const std::string& XmlElement::Prefix() const
{
    return this->_name.Prefix();
}

void XmlElement::SetPrefix(const std::string& prefix)
{
    this->_name = this->_name.OwnerDocument()->AddXmlName(prefix, this->LocalName(), this->NamespaceURI());
}

const XmlName& XmlElement::XmlNameProp() const
{
    return this->_name;
}





/*
 * XmlDocumentType
 */
XmlDocumentType::XmlDocumentType(XmlDocument* ownerDocument, const std::string& name, const std::string& publicId, const std::string& systemId, const std::string& internalSubset)
    : XmlLinkedNode(ownerDocument), _name(name), _publicId(publicId), _systemId(systemId), _internalSubset(internalSubset)
{ }

XmlDocumentType::~XmlDocumentType()
{
    this->RemoveAll();
}

const std::string& XmlDocumentType::InternalSubset()
{
    return this->_internalSubset;
}

const std::string& XmlDocumentType::LocalName() const
{
    return this->_name;
}

const std::string& XmlDocumentType::Name() const
{
    return this->_name;
}

const std::string& XmlDocumentType::NamespaceURI() const
{
    static std::string XmlDocumentTypeNamespaceURI = "";

    return XmlDocumentTypeNamespaceURI;
}

const std::string& XmlDocumentType::Prefix() const
{
    static std::string XmlDocumentTypePrefix = "";

    return XmlDocumentTypePrefix;
}

void XmlDocumentType::SetPrefix(const std::string& prefix)
{ }

const std::string& XmlDocumentType::PublicId()
{
    return this->_publicId;
}

const std::string& XmlDocumentType::SystemId()
{
    return this->_systemId;
}





/*
 * XmlCharacterData
 */
XmlCharacterData::XmlCharacterData(XmlDocument* ownerDocument)
    : XmlLinkedNode(ownerDocument)
{ }

XmlCharacterData::XmlCharacterData(XmlDocument* ownerDocument, const std::string& text)
    : XmlLinkedNode(ownerDocument), _data(text)
{ }

XmlCharacterData::~XmlCharacterData()
{ }

std::string XmlCharacterData::Data()
{
    return this->_data;
}

std::string XmlCharacterData::InnerText()
{
    return this->_data;
}

void XmlCharacterData::SetInnerText(const std::string& innerText)
{
    this->_data = innerText;
}

int XmlCharacterData::Length()
{
    return int(this->_data.size());
}

const std::string& XmlCharacterData::NamespaceURI() const
{
    static std::string XmlCharacterDataNamespaceURI = "";

    return XmlCharacterDataNamespaceURI;
}

void XmlCharacterData::SetNamespaceURI(const std::string& /*namespaceURI*/)
{ }

std::string XmlCharacterData::Value()
{
    return this->_data;
}

void XmlCharacterData::SetValue(const std::string& value)
{
    this->_data = value;
}

const std::string& XmlCharacterData::Prefix() const
{
    static std::string XmlCharacterDataPrefix = "";

    return XmlCharacterDataPrefix;
}

void XmlCharacterData::SetPrefix(const std::string& prefix)
{ }





/*
 * XmlCDataSection
 */
XmlCDataSection::XmlCDataSection(XmlDocument* ownerDocument, const std::string& text)
    : XmlCharacterData(ownerDocument, text)
{ }

XmlCDataSection::~XmlCDataSection()
{ }

const std::string& XmlCDataSection::LocalName() const
{
    static std::string CDataSectionLocalName = "#cdata-section";

    return CDataSectionLocalName;
}

const std::string& XmlCDataSection::Name() const
{
    return this->LocalName();
}





/*
 * XmlComment
 */
XmlComment::XmlComment(XmlDocument* ownerDocument, const std::string& text)
    : XmlCharacterData(ownerDocument, text)
{ }

XmlComment::~XmlComment()
{ }

const std::string& XmlComment::LocalName() const
{
    static std::string CommentLocalName = "#comment";

    return CommentLocalName;
}

const std::string& XmlComment::Name() const
{
    return this->LocalName();
}





/*
 * XmlText
 */
XmlText::XmlText(XmlDocument* ownerDocument, const std::string& text)
    : XmlCharacterData(ownerDocument, text)
{ }

XmlText::~XmlText()
{ }

const std::string& XmlText::LocalName() const
{
    static std::string CommentLocalName = "#text";

    return CommentLocalName;
}

const std::string& XmlText::Name() const
{
    return this->LocalName();
}





/*
 * XmlDocument
 */
XmlDocument::XmlDocument()
    : XmlNode(this)
{ }

XmlDocument::~XmlDocument()
{ }

XmlElement* XmlDocument::DocumentElement()
{
    return (XmlElement*)this->FindChild(XmlNodeType::Element);
}

const std::string& XmlDocument::LocalName() const
{
    static std::string documentLocalName = "#document";

    return documentLocalName;
}

const std::string& XmlDocument::Name() const
{
    return this->LocalName();
}

const std::string& XmlDocument::NamespaceURI() const
{
    static std::string documentNamespaceURI = "";

    return documentNamespaceURI;
}

const std::string& XmlDocument::Prefix() const
{
    static std::string documentPrefix = "";

    return documentPrefix;
}

void XmlDocument::SetPrefix(const std::string& prefix)
{ }

XmlAttribute* XmlDocument::CreateAttribute(const std::string& name)
{
    return new XmlAttribute(this, "", name, "");
}

XmlAttribute* XmlDocument::CreateAttribute(const std::string& name, const std::string& namespaceURI)
{
    return new XmlAttribute(this, "", name, namespaceURI);
}

XmlAttribute* XmlDocument::CreateAttribute(const std::string& prefix, const std::string& localName, const std::string& namespaceURI)
{
    return new XmlAttribute(this, prefix, localName, namespaceURI);
}

XmlCDataSection* XmlDocument::CreateCDataSection(const std::string& text)
{
    return new XmlCDataSection(this, text);
}

XmlComment* XmlDocument::CreateComment(const std::string& text)
{
    return new XmlComment(this, text);
}

XmlDocumentType* XmlDocument::CreateDocumentType(const std::string& name, const std::string& publicId, const std::string& systemId, const std::string& internalSubset)
{
    return new XmlDocumentType(this, name, publicId, systemId, internalSubset);
}

XmlElement* XmlDocument::CreateElement(const std::string& name)
{
    return new XmlElement(this, name);
}

XmlElement* XmlDocument::CreateElement(const std::string& name, const std::string& namespaceURI)
{
    return new XmlElement(this, "", name, namespaceURI);
}

XmlElement* XmlDocument::CreateElement(const std::string& prefix, const std::string& localName, const std::string& namespaceURI)
{
    return new XmlElement(this, prefix, localName, namespaceURI);
}

XmlProcessingInstruction* XmlDocument::CreateProcessingInstruction(const std::string& target, const std::string& data)
{
    return new XmlProcessingInstruction(target, data, this);
}

XmlText* XmlDocument::CreateTextNode(const std::string& text)
{
    return new XmlText(this, text);
}

XmlName XmlDocument::AddXmlName(const std::string& prefix, const std::string& localName, const std::string& ns)
{
    return XmlName(prefix, localName, ns, this);
}

void XmlDocument::LoadXml(const std::string& xml)
{
    std::stringstream ss(xml);
    XmlLoader loader;
    loader.Load(*this, ss);
}





/*
 * XmlLoader
 */
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





/*
 * XmlWriter
 */
XmlWriter::XmlWriter()
{ }

XmlWriter::~XmlWriter()
{ }

std::string XmlWriter::Write(XmlDocument& doc)
{
    std::stringstream result;

    XmlNodeList children = doc.ChildNodes();
    for (int i = 0; i < children.Count(); i++)
        this->WriteNode(children[i], result, 0);

    return result.str();
}

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

void XmlWriter::WriteNode(XmlNode* node, std::stringstream& result, int depth)
{
    if (node->NodeType() == XmlNodeType::Element)
    {
        XmlNodeList children = node->ChildNodes();
        XmlAttributeCollection attrs = node->Attributes();
        bool compact = children.Count() == 1 && children[0]->NodeType() == XmlNodeType::Text;

        result << std::endl;
        for (int i = 0; i < depth; i++)
            result << "\t";
        result << "<" << node->Name();
        for (int i = 0; i < attrs.Count(); i++)
            result << " " << attrs.ItemAt(i)->Name() << "=\"" << attrs.ItemAt(i)->Value() << "\"";
        if (children.Count() == 0)
        {
            result<< " />";
        }
        else
        {
            result<< ">";

            for (int i = 0; i < children.Count(); i++)
                this->WriteNode(children[i], result, depth + 1);

            if (compact == false)
            {
                result << std::endl;
                for (int i = 0; i < depth; i++)
                    result << "\t";
            }
            result << "</" << node->Name() << ">";
        }
    }
    else if (node->NodeType() == XmlNodeType::CDATA)
    {
        for (int i = 0; i < depth; i++)
            result << "\t";
        result << "<![CDATA[" << node->Value() << "]]>";
    }
    else if (node->NodeType() == XmlNodeType::Comment)
    {
        result << std::endl;
        for (int i = 0; i < depth; i++)
            result << "\t";
        result << "<!--" << node->Value() << "-->";
    }
    else if (node->NodeType() == XmlNodeType::ProcessingInstruction)
    {
        XmlAttributeCollection attrs = node->Attributes();

        result << std::endl;
        for (int i = 0; i < depth; i++)
            result << "\t";
        result << "<?" << node->Name();
        for (int i = 0; i < attrs.Count(); i++)
            result << " " << attrs.ItemAt(i)->Name() << "=\"" << attrs.ItemAt(i)->Value() << "\"";
        result << " ?>";
    }
    else if (node->NodeType() == XmlNodeType::DocumentType)
    {
        XmlDocumentType* docType = (XmlDocumentType*)node;
        result << std::endl;
        for (int i = 0; i < depth; i++)
            result << "\t";
        result << "<!DOCTYPE " << node->Name();
        if (docType->PublicId() != "")
            result << " PUBLIC " << docType->PublicId();
        else if (docType->SystemId() != "")
            result << " SYSTEM " << docType->SystemId();
        result << ">";
    }
    else if (node->NodeType() == XmlNodeType::Text)
    {
        std::string val = node->Value();
        trim(val);
        if (val != "")
            result << val;
    }
}





/*
 * XmlException
 */
XmlException::XmlException(const std::string& message)
    : _message(message)
{ }

XmlException::XmlException(const XmlException& other)
    : _message(other.Message())
{ }

XmlException::~XmlException()
{ }

const std::string& XmlException::Message() const
{
    return this->_message;
}
