#include <XmlLinkedNode.h>
#include <XmlDocument.h>

using namespace System::Xml;

XmlLinkedNode::XmlLinkedNode(XmlDocument* ownerDocument)
    : XmlNode(ownerDocument), _next(nullptr)
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
