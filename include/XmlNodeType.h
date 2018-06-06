#ifndef XMLNODETYPE_H
#define XMLNODETYPE_H

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

}
}

#endif // XMLNODETYPE_H
