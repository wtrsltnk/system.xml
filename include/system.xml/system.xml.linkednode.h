#ifndef _SYSTEM_XML_LINKEDNODE_H_
#define _SYSTEM_XML_LINKEDNODE_H_

#include "system.xml.node.h"

namespace System {
namespace Xml {

class XmlLinkedNode : public XmlNode
{
    friend class XmlNode;

protected:
    XmlLinkedNode(class XmlDocument *doc);

public:
    virtual ~XmlLinkedNode();

    // Properties
public:
    // Gets the node immediately following this node.
    virtual XmlNode *NextSibling();

    // Gets the node immediately preceding this node.
    virtual XmlNode *PreviousSibling();

    // Methods
public:
    // Adds the specified node to the end of the list of child nodes, of this node.
    void AppendChild(XmlNode *child);

private:
    XmlLinkedNode *_next;
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_LINKEDNODE_H_
