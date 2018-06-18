#ifndef XMLTEXT_H
#define XMLTEXT_H

#include "XmlCharacterData.h"
#include "XmlNodeType.h"

#include <string>

namespace System
{
namespace Xml
{

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

}
}

#endif // XMLTEXT_H
