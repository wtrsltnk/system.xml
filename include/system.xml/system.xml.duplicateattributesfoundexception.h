#ifndef _SYSTEM_XML_DUPLICATEATTRIBUTESFOUNDEXCEPTION_H_
#define _SYSTEM_XML_DUPLICATEATTRIBUTESFOUNDEXCEPTION_H_

#include "system.xml.exception.h"

namespace System {
namespace Xml {

class XmlDuplicateAttributesFoundException : public XmlException
{
public:
    XmlDuplicateAttributesFoundException() : XmlException("An attribute key can only be added once") {}
    virtual ~XmlDuplicateAttributesFoundException() {}
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_DUPLICATEATTRIBUTESFOUNDEXCEPTION_H_
