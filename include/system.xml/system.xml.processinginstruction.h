#ifndef _SYSTEM_XML_PROCESSINGINSTRUCTION_H_
#define _SYSTEM_XML_PROCESSINGINSTRUCTION_H_

#include "system.xml.linkednode.h"
#include "system.xml.nodetype.h"

#include <string>

namespace System {
namespace Xml {

class XmlProcessingInstruction : public XmlLinkedNode
{
    friend class XmlDocument;

protected:
    XmlProcessingInstruction(const std::string &target, const std::string &data, XmlDocument *ownerDocument);

public:
    virtual ~XmlProcessingInstruction();

    // Properties
public:
    // Gets or sets the content of the processing instruction, excluding the target.
    virtual const std::string &Data() const;
    virtual void SetData(const std::string &data);

    // Gets or sets the concatenated values of the node and all its child nodes.
    virtual std::string InnerText();
    virtual void SetInnerText(const std::string &innerText);

    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string &LocalName() const;

    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string &Name() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::ProcessingInstruction; }

    // Gets the target of the processing instruction.
    virtual const std::string &Target() const;

    // Gets the namespace URI of this node.
    virtual const std::string &NamespaceURI() const;
    virtual void SetNamespaceURI(const std::string &namespaceURI);

    // Gets or sets the value of the node.
    virtual std::string Value();
    virtual void SetValue(const std::string &value);

    // Gets or sets the namespace prefix of this node.
    virtual const std::string &Prefix() const;
    virtual void SetPrefix(const std::string &prefix);

private:
    std::string _target;
    std::string _data;
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_PROCESSINGINSTRUCTION_H_
