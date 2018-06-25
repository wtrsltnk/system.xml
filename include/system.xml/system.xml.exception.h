#ifndef _SYSTEM_XML_EXCEPTION_H_
#define _SYSTEM_XML_EXCEPTION_H_

#include <string>

namespace System {
namespace Xml {

class XmlException
{
public:
    XmlException(const std::string &message);
    XmlException(const XmlException &other);
    virtual ~XmlException();

    // Properties
public:
    // Gets the root XmlElement for the document.
    const std::string &Message() const;

private:
    std::string _message;
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_EXCEPTION_H_
