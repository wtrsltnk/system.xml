#ifndef _SYSTEM_XML_UNEXPECTEDENDOFFILEEXCEPTION_H_
#define _SYSTEM_XML_UNEXPECTEDENDOFFILEEXCEPTION_H_

#include "system.xml.exception.h"

namespace System {
namespace Xml {

class XmlUnexpectedEndOfFileException : public XmlException
{
public:
    XmlUnexpectedEndOfFileException() : XmlException("Unexpected end of file") {}
    virtual ~XmlUnexpectedEndOfFileException() {}
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_UNEXPECTEDENDOFFILEEXCEPTION_H_
