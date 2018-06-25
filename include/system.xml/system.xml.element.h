#ifndef _SYSTEM_XML_ELEMENT_H_
#define _SYSTEM_XML_ELEMENT_H_

#include "system.xml.linkednode.h"
#include "system.xml.name.h"
#include "system.xml.nodetype.h"

#include <string>

namespace System {
namespace Xml {

class XmlElement : public XmlLinkedNode
{
    friend class XmlDocument;

protected:
    XmlElement(XmlDocument *ownerDocument, const std::string &name);
    XmlElement(XmlDocument *ownerDocument, const std::string &prefix, const std::string &localName, const std::string &ns);

public:
    virtual ~XmlElement();

    // Properties
public:
    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string &LocalName() const;

    // Gets the qualified name of the node, when overridden in a derived class.
    virtual const std::string &Name() const;

    // Gets the namespace URI of this node.
    virtual const std::string &NamespaceURI() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::Element; }

    // Gets or sets the namespace prefix of this node.
    virtual const std::string &Prefix() const;
    virtual void SetPrefix(const std::string &prefix);

protected:
    virtual const XmlName *XmlNameProp() const;

private:
    XmlName *_name;
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_ELEMENT_H_
