#ifndef _SYSTEM_XML_UNEXPECTEDCLOSINGTAGEXCEPTION_H_
#define _SYSTEM_XML_UNEXPECTEDCLOSINGTAGEXCEPTION_H_

#include "system.xml.exception.h"

namespace System {
namespace Xml {

class XmlUnexpectedClosingTagException : public XmlException
{
public:
    XmlUnexpectedClosingTagException() : XmlException("Unexpected closing tag") {}
    virtual ~XmlUnexpectedClosingTagException() {}
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_UNEXPECTEDCLOSINGTAGEXCEPTION_H_
