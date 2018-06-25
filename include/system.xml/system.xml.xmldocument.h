#ifndef XMLDOCUMENT_H
#define XMLDOCUMENT_H

#include "system.xml.xmlattribute.h"
#include "system.xml.xmlcdatasection.h"
#include "system.xml.xmlcomment.h"
#include "system.xml.xmldocumentType.h"
#include "system.xml.xmlelement.h"
#include "system.xml.xmlnode.h"
#include "system.xml.xmlnodetype.h"
#include "system.xml.xmlprocessinginstruction.h"
#include "system.xml.xmltext.h"
#include "system.xml/system.xml.xmlnametable.h"
#include <string>

namespace System {
namespace Xml {

class XmlDocument : public XmlNode
{
public:
    XmlDocument();
    virtual ~XmlDocument();

    // Properties
public:
    // Gets the root XmlElement for the document.
    XmlElement *DocumentElement();

    // Gets the node containing the DOCTYPE declaration.
    XmlDocumentType *DocumentType();

    // Gets the local name of the node. (Overrides XmlNode.LocalName.)
    const std::string &LocalName() const;

    // Gets the qualified name of the node. (Overrides XmlNode.Name.)
    const std::string &Name() const;

    // Gets the namespace URI of this node.
    virtual const std::string &NamespaceURI() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::Document; }

    // Gets or sets the namespace prefix of this node.
    virtual const std::string &Prefix() const;
    virtual void SetPrefix(const std::string &prefix);

    // Methods
public:
    // Loads the XML document from the specified URL.
    void Load(const std::string &filename);

    // Loads the XML document from the specified string.
    void LoadXml(const std::string &xml);

    // Saves the XML document to the specified file. If the specified file exists, this method overwrites it.
    void Save(const std::string &filename);

    // Static Methods
public:
    // Creates an XmlAttribute with the specified Name.
    XmlAttribute *CreateAttribute(const std::string &name);

    // Creates an XmlAttribute with the specified qualified name and NamespaceURI.
    XmlAttribute *CreateAttribute(const std::string &name, const std::string &namespaceURI);

    // Creates an XmlAttribute with the specified Prefix, LocalName, and NamespaceURI.
    XmlAttribute *CreateAttribute(const std::string &prefix, const std::string &localName, const std::string &namespaceURI);

    // Creates an XmlCDataSection containing the specified data.
    XmlCDataSection *CreateCDataSection(const std::string &text = "");

    // Creates an XmlComment containing the specified data.
    XmlComment *CreateComment(const std::string &text = "");
    /*
    // Creates a default attribute with the specified prefix, local name and namespace URI.
    CreateDefaultAttribute

    // Creates an XmlDocumentFragment.
    CreateDocumentFragment
*/
    // Returns a new XmlDocumentType object.
    XmlDocumentType *CreateDocumentType(const std::string &name, const std::string &publicId, const std::string &systemId, const std::string &internalSubset);

    // Creates an element with the specified name.
    XmlElement *CreateElement(const std::string &name);

    // Creates an XmlElement with the qualified name and NamespaceURI.
    XmlElement *CreateElement(const std::string &name, const std::string &namespaceURI);

    // Creates an element with the specified Prefix, LocalName, and NamespaceURI.
    XmlElement *CreateElement(const std::string &prefix, const std::string &localName, const std::string &namespaceURI);

    // Creates an XmlNode with the specified node type, Name, and NamespaceURI.
    XmlNode *CreateNode(const std::string &nodeType, const std::string &name, const std::string &namespaceURI);

    // Creates an XmlNode with the specified XmlNodeType, Name, and NamespaceURI.
    XmlNode *CreateNode(XmlNodeType::Type nodeType, const std::string &name, const std::string &namespaceURI);

    // Creates a XmlNode with the specified XmlNodeType, Prefix, Name, and NamespaceURI.
    XmlNode *CreateNode(XmlNodeType::Type nodeType, const std::string &prefix, const std::string &localName, const std::string &namespaceURI);

    // Creates an XmlProcessingInstruction with the specified name and data.
    XmlProcessingInstruction *CreateProcessingInstruction(const std::string &target, const std::string &data);
    /*
    // Creates an XmlSignificantWhitespace node.
    CreateSignificantWhitespace
*/
    // Creates an XmlText with the specified text.
    XmlText *CreateTextNode(const std::string &text = "");
    /*
    // Creates an XmlWhitespace node.
    CreateWhitespace

    // Creates an XmlDeclaration node with the specified values.
    CreateXmlDeclaration
*/
private:
    XmlName *AddXmlName(const std::string &prefix, const std::string &localName, const std::string &ns);

    std::vector<XmlName *> _nameTable;
    friend class XmlElement;
    friend class XmlAttribute;
};

} // namespace Xml
} // namespace System

#endif // XMLDOCUMENT_H
