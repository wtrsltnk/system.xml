#ifndef XMLCOMMENT_H
#define XMLCOMMENT_H

#include "system.xml.xmlcharacterdata.h"
#include "system.xml.xmlnodetype.h"

#include <string>

namespace System
{
namespace Xml
{

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

}
}

#endif // XMLCOMMENT_H
