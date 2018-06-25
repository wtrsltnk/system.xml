#ifndef XMLDOCUMENTTYPE_H
#define XMLDOCUMENTTYPE_H

#include "system.xml.xmllinkednode.h"
#include "system.xml.xmlnodetype.h"

#include <string>

namespace System
{
namespace Xml
{

class XmlDocumentType : public XmlLinkedNode
{
    friend class XmlDocument;
protected:
    XmlDocumentType(class XmlDocument* ownerDocument, const std::string& name, const std::string& publicId, const std::string& systemId, const std::string& internalSubset);

public:
    virtual ~XmlDocumentType();

    // Properties
public:
    // Gets the entire value of the DTD internal subset on the DOCTYPE declaration.
    const std::string& InternalSubset();

    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string& LocalName() const;

    // Gets the qualified name of the node, when overridden in a derived class.
    virtual const std::string& Name() const;

    // Gets the namespace URI of this node.
    virtual const std::string& NamespaceURI() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::DocumentType; }

    // Gets or sets the namespace prefix of this node.
    virtual const std::string& Prefix() const;
    virtual void SetPrefix(const std::string& prefix);

    // Gets the value of the public identifier on the DOCTYPE declaration.
    const std::string& PublicId();

    // Gets the value of the system identifier on the DOCTYPE declaration.
    const std::string& SystemId();
private:
    std::string _name;
    std::string _publicId;
    std::string _systemId;
    std::string _internalSubset;
};

}
}

#endif // XMLDOCUMENTTYPE_H
