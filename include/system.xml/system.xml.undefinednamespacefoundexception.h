#ifndef _SYSTEM_XML_UNDEFINEDNAMESPACEFOUNDEXCEPTION_H_
#define _SYSTEM_XML_UNDEFINEDNAMESPACEFOUNDEXCEPTION_H_

#include "system.xml.exception.h"

#include <string>

namespace System {
namespace Xml {

class XmlUndefinedNamespaceFoundException : public XmlException
{
private:
    std::string _prefix;

public:
    XmlUndefinedNamespaceFoundException(const std::string &prefix) : XmlException("Undefined namespace found"), _prefix(prefix) {}
    virtual ~XmlUndefinedNamespaceFoundException() {}

    const std::string &Prefix() const { return this->_prefix; }
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_UNDEFINEDNAMESPACEFOUNDEXCEPTION_H_
