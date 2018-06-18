#include <system.xml/XmlDocument.h>
#include <system.xml/XmlLinkedNode.h>

using namespace System::Xml;

XmlLinkedNode::XmlLinkedNode(XmlDocument *ownerDocument)
    : XmlNode(ownerDocument), _next(nullptr)
{}

XmlLinkedNode::~XmlLinkedNode()
{}

XmlNode *XmlLinkedNode::PreviousSibling()
{
    XmlNode *parent = this->ParentNode();
    if (parent == 0)
    {
        return 0;
    }

    XmlNode *node = parent->FirstChild();
    while (node != 0)
    {
        XmlNode *nextSibling = node->NextSibling();
        if (nextSibling == this || nextSibling == 0)
            break;
        node = nextSibling;
    }

    return node;
}

XmlNode *XmlLinkedNode::NextSibling()
{
    XmlNode *parent = this->ParentNode();
    if (parent != 0)
    {
        if (this != parent->LastChild())
            return this->_next;
    }
    return 0;
}
