#include <system.xml/system.xml.exception.h>

using namespace System::Xml;

XmlException::XmlException(const std::string &message)
    : _message(message)
{}

XmlException::XmlException(const XmlException &other)
    : _message(other.Message())
{}

XmlException::~XmlException()
{}

const std::string &XmlException::Message() const
{
    return this->_message;
}
