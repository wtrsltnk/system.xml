#ifndef XMLUNEXPECTEDCLOSINGTAGEXCEPTION_H
#define XMLUNEXPECTEDCLOSINGTAGEXCEPTION_H

#include "system.xml.xmlexception.h"

namespace System
{
namespace Xml
{

class XmlUnexpectedClosingTagException : public XmlException
{
public:
    XmlUnexpectedClosingTagException() : XmlException("Unexpected closing tag") { }
    virtual ~XmlUnexpectedClosingTagException() { }
};

}
}

#endif // XMLUNEXPECTEDCLOSINGTAGEXCEPTION_H
