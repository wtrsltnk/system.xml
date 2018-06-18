#include <iostream>
#include <sstream>
#include <system.xml/XmlDocument.h>
#include <system.xml/XmlException.h>
#include <system.xml/XmlNode.h>

using namespace System::Xml;

XmlNode::XmlNode(XmlDocument *doc)
    : _parentNode(doc), _lastNode(0)
{}

XmlNode::~XmlNode()
{
    this->Attributes().RemoveAll();
    this->RemoveAll();
}

XmlAttributeCollection &XmlNode::Attributes()
{
    return this->_attributes;
}

void XmlNode::SetAttributes(const XmlAttributeCollection &attrs)
{
    this->_attributes = attrs;
}

XmlNodeList XmlNode::ChildNodes()
{
    return XmlNodeList(this);
}

XmlNode *XmlNode::FirstChild()
{
    XmlLinkedNode *lastNode = this->_lastNode;

    if (lastNode != nullptr && lastNode != this)
    {
        return lastNode->_next;
    }

    return 0;
}

bool XmlNode::HasChildNodes()
{
    return this->_lastNode != 0;
}

XmlNode *XmlNode::PreviousSibling()
{
    return 0;
}

std::string XmlNode::InnerText()
{
    std::stringstream result;

    XmlNodeList childNodes = this->ChildNodes();
    for (int i = 0; i < childNodes.Count(); i++)
    {
        XmlNode *node = childNodes[i];
        result << node->InnerText();
    }

    return result.str();
}

void XmlNode::SetInnerText(const std::string &innerText)
{
    XmlNode *firstChild = this->FirstChild();

    if (firstChild != 0 && firstChild->NextSibling() != 0 && firstChild->NodeType() == XmlNodeType::Text)
    {
        firstChild->SetValue(innerText);
    }
    else
    {
        this->RemoveAll();
        this->AppendChild(this->OwnerDocument()->CreateTextNode(innerText));
    }
}

XmlNode *XmlNode::LastChild()
{
    return this->_lastNode;
}

std::string XmlNode::InnerXml()
{
    std::stringstream result;

    for (int i = 0; i < this->ChildNodes().Count(); i++)
    {
        result << this->ChildNodes()[i]->OuterXml();
    }

    return result.str();
}

void XmlNode::SetInnerXml(const std::string & /*innerXml*/)
{}

XmlNode *XmlNode::NextSibling()
{
    return 0;
}

std::string XmlNode::OuterXml()
{
    std::stringstream result;

    result << "<" << this->Name();

    XmlAttributeCollection::iterator i = this->Attributes().begin();
    for (; i != this->Attributes().end(); ++i)
    {
        result << " " << i->second->Name() << "=\"" << i->second->Value() << "\"";
    }

    result << ">" << this->InnerXml() << "</" << this->Name() << ">";

    return result.str();
}

XmlDocument *XmlNode::OwnerDocument()
{
    if (this->_parentNode->NodeType() == XmlNodeType::Document)
    {
        return (XmlDocument *)this->_parentNode;
    }

    return this->_parentNode->OwnerDocument();
}

XmlNode *XmlNode::ParentNode()
{
    return this->_parentNode;
}

std::string XmlNode::Value()
{
    return "";
}

void XmlNode::SetValue(const std::string &value)
{}

void XmlNode::AppendChild(XmlNode *child)
{
    if (IsAncestor(child))
    {
        throw XmlException("Cannot append ancestor node as child node");
    }

    child->_parentNode = this;
    XmlLinkedNode *linked = reinterpret_cast<XmlLinkedNode *>(child);
    if (linked == nullptr)
    {
        return;
    }

    if (this->_lastNode != nullptr)
    {
        linked->_next = this->_lastNode->_next;
        this->_lastNode->_next = linked;
    }
    else
    {
        linked->_next = linked;
    }

    this->_lastNode = linked;
}

void XmlNode::RemoveAll()
{
    XmlNode *ptr = this->FirstChild();
    while (ptr != 0)
    {
        XmlNode *tmp = ptr->NextSibling();
        this->RemoveChild(ptr);
        delete ptr;
        ptr = tmp;
    }
    this->_lastNode = nullptr;
}

XmlNode *XmlNode::RemoveChild(XmlNode *child)
{
    if (child->_parentNode != this)
    {
        throw XmlException("Argument exception, given child is no child of mine!");
    }

    XmlLinkedNode *childNode = (XmlLinkedNode *)child;
    XmlLinkedNode *prevNode = (XmlLinkedNode *)child->PreviousSibling();
    XmlLinkedNode *nextNode = childNode->_next;

    prevNode->_next = nextNode;
    childNode->_next = 0;
    childNode->_parentNode = 0;

    return childNode;
}

XmlNodeList *XmlNode::SelectNodes(const std::string &xpath)
{
    return nullptr;
}

XmlNode *XmlNode::SelectSingleNode(const std::string &xpath)
{
    XmlNodeList *list = SelectNodes(xpath);

    if (list != nullptr)
    {
        return list->Item(0);
    }

    return nullptr;
}

XmlNode *XmlNode::FindChild(XmlNodeType::Type type)
{
    XmlNode *find = this->FirstChild();

    while (find != 0)
    {
        if (find->NodeType() == type)
            return find;
        find = find->NextSibling();
    }

    return 0;
}

void XmlNode::SetParent(XmlNode *parent)
{
    if (parent == 0)
        this->_parentNode = this->OwnerDocument();
    else
        this->_parentNode = parent;
}

bool XmlNode::IsAncestor(XmlNode *node)
{
    if (node == this)
    {
        return true;
    }

    return _parentNode != nullptr && _parentNode != this ? _parentNode->IsAncestor(node) : false;
}
