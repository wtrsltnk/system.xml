#ifndef XMLUNEXPECTEDCHARACTEREXCEPTION_H
#define XMLUNEXPECTEDCHARACTEREXCEPTION_H

#include "system.xml.xmlexception.h"

namespace System
{
namespace Xml
{

class XmlUnexpectedCharacterException : public XmlException
{
    char _found;
    char _expected;
public:
    XmlUnexpectedCharacterException(char found, char expected) : XmlException("Unexpected character found"), _found(found), _expected(expected) { }
    virtual ~XmlUnexpectedCharacterException() { }

    char Found() const { return _found; }
    char Expected() const { return _expected; }
};

}
}

#endif // XMLUNEXPECTEDCHARACTEREXCEPTION_H
