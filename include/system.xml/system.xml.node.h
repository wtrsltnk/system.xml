#ifndef _SYSTEM_XML_NODE_H_
#define _SYSTEM_XML_NODE_H_

#include "system.xml.attributecollection.h"
#include "system.xml.nodelist.h"
#include "system.xml.nodetype.h"

#include <string>

namespace System {
namespace Xml {

class XmlNode
{
    friend class XmlDocument;

protected:
    XmlNode(class XmlDocument *doc);

public:
    virtual ~XmlNode();

    // Properties
public:
    // Gets an XmlAttributeCollection containing the attributes of this node.
    XmlAttributeCollection &Attributes();
    void SetAttributes(const XmlAttributeCollection &attrs);

    // Gets all the child nodes of the node.
    XmlNodeList ChildNodes();

    // Gets the first child of the node.
    XmlNode *FirstChild();

    // Gets a value indicating whether this node has any child nodes.
    bool HasChildNodes();

    // Gets or sets the concatenated values of the node and all its child nodes.
    virtual std::string InnerText();
    virtual void SetInnerText(const std::string &innerText);

    // Gets or sets the markup representing only the child nodes of this node.
    std::string InnerXml();
    void SetInnerXml(const std::string &innerXml);

    // Gets the last child of the node.
    XmlNode *LastChild();

    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string &LocalName() const = 0;

    // Gets the qualified name of the node, when overridden in a derived class.
    virtual const std::string &Name() const = 0;

    // Gets the namespace URI of this node.
    virtual const std::string &NamespaceURI() const = 0;

    // Gets the node immediately following this node.
    virtual XmlNode *NextSibling();

    // Gets the type of the current node, when overridden in a derived class.
    virtual XmlNodeType::Type NodeType() = 0;

    // Gets the markup containing this node and all its child nodes.
    virtual std::string OuterXml();

    // Gets the XmlDocument to which this node belongs.
    class XmlDocument *OwnerDocument();

    // Gets the parent of this node (for nodes that can have parents).
    XmlNode *ParentNode();

    // Gets or sets the namespace prefix of this node.
    virtual const std::string &Prefix() const = 0;
    virtual void SetPrefix(const std::string &prefix) = 0;

    // Gets the node immediately preceding this node.
    virtual XmlNode *PreviousSibling();

    // Gets or sets the value of the node.
    virtual std::string Value();
    virtual void SetValue(const std::string &value);

    // Methods
public:
    // Adds the specified node to the end of the list of child nodes, of this node.
    void AppendChild(XmlNode *child);

    // Removes all the child nodes and/or attributes of the current node.
    void RemoveAll();

    // Removes specified child node.
    XmlNode *RemoveChild(XmlNode *child);

    //Selects a list of nodes matching the XPath expression.
    class XmlNodeList *SelectNodes(const std::string &xpath);

    //Selects a list of nodes matching the XPath expression.
    XmlNode *SelectSingleNode(const std::string &xpath);

protected:
    class XmlLinkedNode *_lastNode;

    XmlNode *FindChild(XmlNodeType::Type type);

private:
    XmlNode *_parentNode;
    XmlAttributeCollection _attributes;

    void SetParent(XmlNode *parent);
    bool IsAncestor(XmlNode *node);
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_NODE_H_
