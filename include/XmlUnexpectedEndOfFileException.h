#ifndef XMLUNEXPECTEDENDOFFILEEXCEPTION_H
#define XMLUNEXPECTEDENDOFFILEEXCEPTION_H

#include "XmlException.h"

namespace System
{
namespace Xml
{

class XmlUnexpectedEndOfFileException : public XmlException
{
public:
    XmlUnexpectedEndOfFileException() : XmlException("Unexpected end of file") { }
    virtual ~XmlUnexpectedEndOfFileException() { }
};

}
}

#endif // XMLUNEXPECTEDENDOFFILEEXCEPTION_H
