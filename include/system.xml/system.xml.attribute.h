#ifndef _SYSTEM_XML_ATTRIBUTE_H_
#define _SYSTEM_XML_ATTRIBUTE_H_

#include "system.xml.name.h"
#include "system.xml.node.h"

#include <string>

namespace System {
namespace Xml {

class XmlAttribute : public XmlNode
{
    friend class XmlDocument;

protected:
    XmlAttribute(XmlDocument *ownerDocument, const std::string &name);
    XmlAttribute(XmlDocument *ownerDocument, const std::string &prefix, const std::string &localName, const std::string &ns);

public:
    virtual ~XmlAttribute();

    // Properties
public:
    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string &LocalName() const;

    // Gets the qualified name of the node, when overridden in a derived class.
    virtual const std::string &Name() const;

    // Gets the namespace URI of this node.
    virtual const std::string &NamespaceURI() const;

    // Gets the type of the current node, when overridden in a derived class.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::Attribute; }

    // Gets or sets the namespace prefix of this node.
    virtual const std::string &Prefix() const;
    virtual void SetPrefix(const std::string &prefix);

    // Gets or sets the value of the node.
    virtual std::string Value();
    virtual void SetValue(const std::string &value);

protected:
    virtual const XmlName *XmlNameProp() const;

private:
    XmlName *_name;
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_ATTRIBUTE_H_
