#include <system.xml/XmlDocument.h>
#include <system.xml/XmlName.h>

using namespace System::Xml;

XmlName::XmlName(const std::string &prefix, const std::string &localName, const std::string &ns, XmlDocument *ownerDocument)
    : _prefix(prefix), _localName(localName), _ns(ns), _ownerDocument(ownerDocument)
{
    if (this->_prefix != "")
        this->_name = this->_prefix + ":" + this->_localName;
    else
        this->_name = this->_localName;
}

XmlName::~XmlName()
{}

const std::string &XmlName::LocalName() const
{
    return this->_localName;
}

const std::string &XmlName::Name() const
{
    return this->_name;
}

const std::string &XmlName::NamespaceURI() const
{
    return this->_ns;
}

XmlDocument *XmlName::OwnerDocument()
{
    return this->_ownerDocument;
}

const std::string &XmlName::Prefix() const
{
    return this->_prefix;
}
