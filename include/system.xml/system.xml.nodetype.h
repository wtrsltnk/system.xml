#ifndef _SYSTEM_XML_NODETYPE_H_
#define _SYSTEM_XML_NODETYPE_H_

namespace System {
namespace Xml {

namespace XmlNodeType {
typedef enum {
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

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_NODETYPE_H_
