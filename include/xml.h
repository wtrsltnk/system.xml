#ifndef XML_H
#define XML_H

#include <vector>
#include <map>
#include <string>
#include <fstream>

namespace System
{
namespace Xml
{

namespace XmlNodeType
{
typedef enum
{
    Attribute,
    CDATA,
    Comment,
    Document,
//    DocumentFragment,
    DocumentType,
    Element,
    EndElement,
//    EndEntity,
//    Entity,
//    EntityReference,
    None,
//    Notation,
    ProcessingInstruction,
//    SignificantWhitespace,
    Text,
//    Whitespace,
    XmlDeclaration
} Type;
}

class XmlAttributeCollection : std::map<std::string, class XmlAttribute*>
{
    friend class XmlNode;   // This makes iterating over this std::map easier
protected:
public:
    XmlAttributeCollection();
    virtual ~XmlAttributeCollection();

    // Properties
public:
    // Gets the number of nodes in the XmlNodeList.
    int Count();

    // Gets a node at the given key.
    XmlAttribute* operator[](const std::string& key);

    // Gets a node at the given index.
    XmlAttribute* operator[](int index);

    // Methods
public:
    // Inserts the specified attribute as the last node in the collection.
    XmlAttribute* Append(XmlAttribute* node);

    // Retrieves a node at the given key.
    class XmlAttribute* Item(const std::string& key);

    // Retrieves a node at the given index.
    class XmlAttribute* ItemAt(int index);

    // Removes all attributes from the collection.
    void RemoveAll();

    // Removes the node from the XmlAttributeCollection.
    void RemoveNamedItem(const std::string& name);

    // Removes the node from the XmlAttributeCollection.
    void RemoveNamedItem(const std::string& localName, const std::string& namespaceURI);


};

class XmlNodeList : std::vector<class XmlNode*>
{
    friend class XmlNode;   // This makes iterating over this std::vector easier
public:
    XmlNodeList();
    XmlNodeList(XmlNode* node);
    virtual ~XmlNodeList();

    // Properties
public:
    // Gets the number of nodes in the XmlNodeList.
    int Count();

    // Gets a node at the given index.
    XmlNode* operator[](int index);

    // Methods
public:
    // Retrieves a node at the given index.
    class XmlNode* Item(int index);

};

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

class XmlNode
{
    friend class XmlDocument;

protected:
    XmlNode(class XmlDocument* doc);

public:
    virtual ~XmlNode();

    // Properties
public:
    // Gets an XmlAttributeCollection containing the attributes of this node.
    XmlAttributeCollection& Attributes();
    void SetAttributes(const XmlAttributeCollection& attrs);

    // Gets all the child nodes of the node.
    XmlNodeList ChildNodes();

    // Gets the first child of the node.
    XmlNode* FirstChild();

    // Gets a value indicating whether this node has any child nodes.
    bool HasChildNodes();

    // Gets or sets the concatenated values of the node and all its child nodes.
    virtual std::string InnerText();
    virtual void SetInnerText(const std::string& innerText);

    // Gets or sets the markup representing only the child nodes of this node.
    std::string InnerXml();
    void SetInnerXml(const std::string& innerXml);

    // Gets the last child of the node.
    XmlNode* LastChild();

    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string& LocalName() const = 0;

    // Gets the qualified name of the node, when overridden in a derived class.
    virtual const std::string& Name() const = 0;

    // Gets the namespace URI of this node.
    virtual const std::string& NamespaceURI() const = 0;

    // Gets the node immediately following this node.
    virtual XmlNode* NextSibling();

    // Gets the type of the current node, when overridden in a derived class.
    virtual XmlNodeType::Type NodeType() = 0;

    // Gets the markup containing this node and all its child nodes.
    virtual std::string OuterXml();

    // Gets the XmlDocument to which this node belongs.
    class XmlDocument* OwnerDocument();

    // Gets the parent of this node (for nodes that can have parents).
    XmlNode* ParentNode();

    // Gets or sets the namespace prefix of this node.
    virtual const std::string& Prefix() const = 0;
    virtual void SetPrefix(const std::string& prefix) = 0;

    // Gets the node immediately preceding this node.
    virtual XmlNode* PreviousSibling();

    // Gets or sets the value of the node.
    virtual std::string Value();
    virtual void SetValue(const std::string& value);

    // Methods
public:
    // Adds the specified node to the end of the list of child nodes, of this node.
    void AppendChild(XmlNode* child);

    // Removes all the child nodes and/or attributes of the current node.
    void RemoveAll();

    // Removes specified child node.
    XmlNode* RemoveChild(XmlNode* child);

    //Selects a list of nodes matching the XPath expression.
    class XmlNodeList* SelectNodes(const std::string& xpath);

    //Selects a list of nodes matching the XPath expression.
    XmlNode* SelectSingleNode(const std::string& xpath);

protected:
    class XmlLinkedNode* _lastNode;

    XmlNode* FindChild(XmlNodeType::Type type);

private:
    XmlNode* _parentNode;
    XmlAttributeCollection _attributes;

    void SetParent(XmlNode* parent);
};

class XmlAttribute : public XmlNode
{
    friend class XmlDocument;
protected:
    XmlAttribute(XmlDocument* ownerDocument, const std::string& name);
    XmlAttribute(XmlDocument* ownerDocument, const std::string& prefix, const std::string& localName, const std::string& ns);

public:
    virtual ~XmlAttribute();

    // Properties
public:
    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string& LocalName() const;

    // Gets the qualified name of the node, when overridden in a derived class.
    virtual const std::string& Name() const;

    // Gets the namespace URI of this node.
    virtual const std::string& NamespaceURI() const;

    // Gets the type of the current node, when overridden in a derived class.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::Attribute; }

    // Gets or sets the namespace prefix of this node.
    virtual const std::string& Prefix() const;
    virtual void SetPrefix(const std::string& prefix);

    // Gets or sets the value of the node.
    virtual std::string Value();
    virtual void SetValue(const std::string& value);

protected:
    virtual const XmlName& XmlNameProp() const;

private:
    XmlName _name;

};

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

class XmlProcessingInstruction  : public XmlLinkedNode
{
    friend class XmlDocument;
protected:
    XmlProcessingInstruction(const std::string& target, const std::string& data, XmlDocument* ownerDocument);

public:
    virtual ~XmlProcessingInstruction();

    // Properties
public:
    // Gets or sets the content of the processing instruction, excluding the target.
    virtual const std::string& Data() const;
    virtual void SetData(const std::string& data);

    // Gets or sets the concatenated values of the node and all its child nodes.
    virtual std::string InnerText();
    virtual void SetInnerText(const std::string& innerText);

    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string& LocalName() const;

    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string& Name() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::ProcessingInstruction; }

    // Gets the target of the processing instruction.
    virtual const std::string& Target() const;

    // Gets the namespace URI of this node.
    virtual const std::string& NamespaceURI() const;
    virtual void SetNamespaceURI(const std::string& namespaceURI);

    // Gets or sets the value of the node.
    virtual std::string Value();
    virtual void SetValue(const std::string& value);

    // Gets or sets the namespace prefix of this node.
    virtual const std::string& Prefix() const;
    virtual void SetPrefix(const std::string& prefix);

private:
    std::string _target;
    std::string _data;

};

class XmlElement : public XmlLinkedNode
{
    friend class XmlDocument;
protected:
    XmlElement(XmlDocument* ownerDocument, const std::string& name);
    XmlElement(XmlDocument* ownerDocument, const std::string& prefix, const std::string& localName, const std::string& ns);

public:
    virtual ~XmlElement();

    // Properties
public:
    // Gets the local name of the node, when overridden in a derived class.
    virtual const std::string& LocalName() const;

    // Gets the qualified name of the node, when overridden in a derived class.
    virtual const std::string& Name() const;

    // Gets the namespace URI of this node.
    virtual const std::string& NamespaceURI() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::Element; }

    // Gets or sets the namespace prefix of this node.
    virtual const std::string& Prefix() const;
    virtual void SetPrefix(const std::string& prefix);

protected:
    virtual const XmlName& XmlNameProp() const;

private:
    XmlName _name;

};

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

class XmlCharacterData : public XmlLinkedNode
{
    friend class XmlDocument;
protected:
    XmlCharacterData(class XmlDocument* ownerDocument);
    XmlCharacterData(class XmlDocument* ownerDocument, const std::string& text = "");

public:
    virtual ~XmlCharacterData();

    // Properties
public:
    // Contains the data of the node.
    std::string Data();

    // Gets or sets the concatenated values of the node and all its child nodes.
    virtual std::string InnerText();
    virtual void SetInnerText(const std::string& innerText);

    // Gets the length of the data, in characters.
    int Length();

    // Gets the namespace URI of this node.
    virtual const std::string& NamespaceURI() const;
    virtual void SetNamespaceURI(const std::string& namespaceURI);

    // Gets or sets the value of the node.
    virtual std::string Value();
    virtual void SetValue(const std::string& value);

    // Gets or sets the namespace prefix of this node.
    virtual const std::string& Prefix() const;
    virtual void SetPrefix(const std::string& prefix);

private:
    std::string _data;

};

class XmlCDataSection : public XmlCharacterData
{
    friend class XmlDocument;
protected:
    XmlCDataSection(class XmlDocument* ownerDocument, const std::string& text = "");

public:
    virtual ~XmlCDataSection();

    // Properties
public:
    // Gets the local name of the node. (Overrides XmlNode.LocalName.)
    const std::string& LocalName() const;

    // Gets the qualified name of the node. (Overrides XmlNode.Name.)
    const std::string& Name() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::CDATA; }

};

class XmlComment : public XmlCharacterData
{
    friend class XmlDocument;
protected:
    XmlComment(class XmlDocument* ownerDocument, const std::string& text = "");

public:
    virtual ~XmlComment();

    // Properties
public:
    // Gets the local name of the node. (Overrides XmlNode.LocalName.)
    const std::string& LocalName() const;

    // Gets the qualified name of the node. (Overrides XmlNode.Name.)
    const std::string& Name() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::Comment; }

};

class XmlText : public XmlCharacterData
{
    friend class XmlDocument;
protected:
    XmlText(class XmlDocument* ownerDocument, const std::string& text = "");

public:
    virtual ~XmlText();

    // Properties
public:
    // Gets the local name of the node. (Overrides XmlNode.LocalName.)
    const std::string& LocalName() const;

    // Gets the qualified name of the node. (Overrides XmlNode.Name.)
    const std::string& Name() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::Text; }

};

class XmlDocument : public XmlNode
{
protected:
public:
    XmlDocument();
    virtual ~XmlDocument();

    // Properties
public:
    // Gets the root XmlElement for the document.
    XmlElement* DocumentElement();

    // Gets the node containing the DOCTYPE declaration.
    XmlDocumentType* DocumentType();

    // Gets the local name of the node. (Overrides XmlNode.LocalName.)
    const std::string& LocalName() const;

    // Gets the qualified name of the node. (Overrides XmlNode.Name.)
    const std::string& Name() const;

    // Gets the namespace URI of this node.
    virtual const std::string& NamespaceURI() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::Document; }

    // Gets or sets the namespace prefix of this node.
    virtual const std::string& Prefix() const;
    virtual void SetPrefix(const std::string& prefix);

    // Methods
public:
    // Loads the XML document from the specified URL.
    void Load(const std::string& filename);

    // Loads the XML document from the specified string.
    void LoadXml(const std::string& xml);

    // Saves the XML document to the specified file. If the specified file exists, this method overwrites it.
    void Save(const std::string& filename);

    // Static Methods
public:
    // Creates an XmlAttribute with the specified Name.
    XmlAttribute* CreateAttribute(const std::string& name);

    // Creates an XmlAttribute with the specified qualified name and NamespaceURI.
    XmlAttribute* CreateAttribute(const std::string& name, const std::string& namespaceURI);

    // Creates an XmlAttribute with the specified Prefix, LocalName, and NamespaceURI.
    XmlAttribute* CreateAttribute(const std::string& prefix, const std::string& localName, const std::string& namespaceURI);

    // Creates an XmlCDataSection containing the specified data.
    XmlCDataSection* CreateCDataSection(const std::string& text = "");

    // Creates an XmlComment containing the specified data.
    XmlComment* CreateComment(const std::string& text = "");
/*
    // Creates a default attribute with the specified prefix, local name and namespace URI.
    CreateDefaultAttribute

    // Creates an XmlDocumentFragment.
    CreateDocumentFragment
*/
    // Returns a new XmlDocumentType object.
    XmlDocumentType* CreateDocumentType(const std::string& name, const std::string& publicId, const std::string& systemId, const std::string& internalSubset);

    // Creates an element with the specified name.
    XmlElement* CreateElement(const std::string& name);

    // Creates an XmlElement with the qualified name and NamespaceURI.
    XmlElement* CreateElement(const std::string& name, const std::string& namespaceURI);

    // Creates an element with the specified Prefix, LocalName, and NamespaceURI.
    XmlElement* CreateElement(const std::string& prefix, const std::string& localName, const std::string& namespaceURI);

    // Creates an XmlNode with the specified node type, Name, and NamespaceURI.
    XmlNode* CreateNode(const std::string& nodeType, const std::string& name, const std::string& namespaceURI);

    // Creates an XmlNode with the specified XmlNodeType, Name, and NamespaceURI.
    XmlNode* CreateNode(XmlNodeType::Type nodeType, const std::string& name, const std::string& namespaceURI);

    // Creates a XmlNode with the specified XmlNodeType, Prefix, Name, and NamespaceURI.
    XmlNode* CreateNode(XmlNodeType::Type nodeType, const std::string& prefix, const std::string& localName, const std::string& namespaceURI);

    // Creates an XmlProcessingInstruction with the specified name and data.
    XmlProcessingInstruction* CreateProcessingInstruction(const std::string& target, const std::string& data);
/*
    // Creates an XmlSignificantWhitespace node.
    CreateSignificantWhitespace
*/
    // Creates an XmlText with the specified text.
    XmlText* CreateTextNode(const std::string& text = "");
/*
    // Creates an XmlWhitespace node.
    CreateWhitespace

    // Creates an XmlDeclaration node with the specified values.
    CreateXmlDeclaration
*/
private:
    XmlName AddXmlName(const std::string& prefix, const std::string& localName, const std::string& ns);

    friend class XmlElement;
    friend class XmlAttribute;
};

class XmlLoader
{
public:
    XmlLoader();
    virtual ~XmlLoader();

    void ResetNamespaces();
    void Load(XmlDocument& doc, std::istream& fr);

private:
    bool ParseTag(const char*& ptr, const char* open, const char* close, std::string& output);
    void ParseTagName(const std::string& str, std::string& prefix, std::string& localname);
    void ParseAttributes(const std::string& str, XmlDocument& doc, XmlAttributeCollection& attrs);
    std::string ParseNamespaceURI(const std::string& prefix);

    std::string _currentDefaultNamespace;
    std::map<std::string, std::string> _namespaces;
};

class XmlWriter
{
public:
    XmlWriter();
    virtual ~XmlWriter();

    std::string Write(XmlDocument& doc);

private:
    void WriteNode(XmlNode* node, std::stringstream& result, int depth);
};

class XmlException
{
public:
    XmlException(const std::string& message);
    XmlException(const XmlException& other);
    virtual ~XmlException();

    // Properties
public:
    // Gets the root XmlElement for the document.
    const std::string& Message() const;

private:
    std::string _message;
};

class XmlUnexpectedClosingTagException : public XmlException
{
public:
    XmlUnexpectedClosingTagException() : XmlException("Unexpected closing tag") { }
    virtual ~XmlUnexpectedClosingTagException() { }
};

class XmlUnexpectedEndOfFileException : public XmlException
{
public:
    XmlUnexpectedEndOfFileException() : XmlException("Unexpected end of file") { }
    virtual ~XmlUnexpectedEndOfFileException() { }
};

class XmlUndefinedNamespaceFoundException : public XmlException
{
private:
    std::string _prefix;

public:
    XmlUndefinedNamespaceFoundException(const std::string& prefix) : XmlException("Undefined namespace found"), _prefix(prefix) { }
    virtual ~XmlUndefinedNamespaceFoundException() { }

    const std::string& Prefix() const { return this->_prefix; }
};

}

}

#endif // XML_H
