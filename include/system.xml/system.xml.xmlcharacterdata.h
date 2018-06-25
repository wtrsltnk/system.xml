#ifndef XMLCHARACTERDATA_H
#define XMLCHARACTERDATA_H

#include "system.xml.xmllinkednode.h"

#include <string>

namespace System
{
namespace Xml
{

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

}
}

#endif // XMLCHARACTERDATA_H
