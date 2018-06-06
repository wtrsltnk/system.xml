#ifndef XMLUNDEFINEDNAMESPACEFOUNDEXCEPTION_H
#define XMLUNDEFINEDNAMESPACEFOUNDEXCEPTION_H

#include "XmlException.h"

#include <string>

namespace System
{
namespace Xml
{

class XmlUndefinedNamespaceFoundException : public XmlException
{
private:
    std::string _prefix;

public:
    XmlUndefinedNamespaceFoundException(const std::string& prefix) : XmlException("Undefined namespace found"), _prefix(prefix) { }
    virtual ~XmlUndefinedNamespaceFoundException() { }

    const std::string& Prefix() const { return this->_prefix; }
};

}
}

#endif // XMLUNDEFINEDNAMESPACEFOUNDEXCEPTION_H
