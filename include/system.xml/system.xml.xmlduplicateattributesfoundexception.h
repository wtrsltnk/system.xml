#ifndef XMLDUPLICATEATTRIBUTESFOUNDEXCEPTION_H
#define XMLDUPLICATEATTRIBUTESFOUNDEXCEPTION_H

#include "system.xml.xmlexception.h"

namespace System
{
namespace Xml
{

class XmlDuplicateAttributesFoundException : public XmlException
{
public:
    XmlDuplicateAttributesFoundException() : XmlException("An attribute key can only be added once") { }
    virtual ~XmlDuplicateAttributesFoundException() { }
};

}
}

#endif // XMLDUPLICATEATTRIBUTESFOUNDEXCEPTION_H