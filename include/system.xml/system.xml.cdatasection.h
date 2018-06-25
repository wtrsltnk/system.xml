#ifndef _SYSTEM_XML_CDATASECTION_H_
#define _SYSTEM_XML_CDATASECTION_H_

#include "system.xml.characterdata.h"
#include "system.xml.nodetype.h"

#include <string>

namespace System {
namespace Xml {

class XmlCDataSection : public XmlCharacterData
{
    friend class XmlDocument;

protected:
    XmlCDataSection(class XmlDocument *ownerDocument, const std::string &text = "");

public:
    virtual ~XmlCDataSection();

    // Properties
public:
    // Gets the local name of the node. (Overrides XmlNode.LocalName.)
    const std::string &LocalName() const;

    // Gets the qualified name of the node. (Overrides XmlNode.Name.)
    const std::string &Name() const;

    // Gets the type of the current node.
    virtual XmlNodeType::Type NodeType() { return XmlNodeType::CDATA; }
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_CDATASECTION_H_
