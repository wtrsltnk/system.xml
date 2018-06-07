#ifndef XMLLINKEDNODE_H
#define XMLLINKEDNODE_H

#include "XmlNode.h"

namespace System
{
namespace Xml
{

class XmlLinkedNode : public XmlNode
{
    friend class XmlNode;
protected:
    XmlLinkedNode(class XmlDocument* doc);

public:
    virtual ~XmlLinkedNode();

    // Properties
public:
    // Gets the node immediately following this node.
    virtual XmlNode* NextSibling();

    // Gets the node immediately preceding this node.
    virtual XmlNode* PreviousSibling();

    // Methods
public:
    // Adds the specified node to the end of the list of child nodes, of this node.
    void AppendChild(XmlNode* child);

private:
    XmlLinkedNode* _next;

};

}
}

#endif // XMLLINKEDNODE_H
