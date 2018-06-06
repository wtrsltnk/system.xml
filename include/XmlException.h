#ifndef XMLEXCEPTION_H
#define XMLEXCEPTION_H

#include <string>

namespace System
{
namespace Xml
{

class XmlException
{
public:
    XmlException(const std::string& message);
    XmlException(const XmlException& other);
    virtual ~XmlException();

    // Properties
public:
    // Gets the root XmlElement for the document.
    const std::string& Message() const;

private:
    std::string _message;
};

}
}

#endif // XMLEXCEPTION_H
