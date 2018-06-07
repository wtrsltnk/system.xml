#ifndef XMLNAME_H
#define XMLNAME_H

#include <string>

namespace System
{
namespace Xml
{

class XmlName
{
public:
    XmlName(const std::string& prefix, const std::string& localName, const std::string& ns, class XmlDocument* ownerDocument);
    virtual ~XmlName();

    // Properties
public:
    // Gets the local name of the node, when overridden in a derived class.
    const std::string& LocalName() const;

    // Gets the qualified name of the node, when overridden in a derived class.
    const std::string& Name() const;

    // Gets the namespace URI of this node.
    const std::string& NamespaceURI() const;

    // Gets the XmlDocument to which the current node belongs.
    class XmlDocument* OwnerDocument();

    // Gets the namespace prefix of this node.
    const std::string& Prefix() const;

private:
    std::string _prefix;
    std::string _localName;
    std::string _ns;
    std::string _name;
    class XmlDocument* _ownerDocument;

};

}
}

#endif // XMLNAME_H