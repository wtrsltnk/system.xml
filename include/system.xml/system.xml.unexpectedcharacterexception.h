#ifndef _SYSTEM_XML_UNEXPECTEDCHARACTEREXCEPTION_H_
#define _SYSTEM_XML_UNEXPECTEDCHARACTEREXCEPTION_H_

#include "system.xml.exception.h"

namespace System {
namespace Xml {

class XmlUnexpectedCharacterException : public XmlException
{
    char _found;
    char _expected;

public:
    XmlUnexpectedCharacterException(char found, char expected) : XmlException("Unexpected character found"), _found(found), _expected(expected) {}
    virtual ~XmlUnexpectedCharacterException() {}

    char Found() const { return _found; }
    char Expected() const { return _expected; }
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_UNEXPECTEDCHARACTEREXCEPTION_H_
