#include <xml/XmlAttribute.h>
#include <xml/XmlDocument.h>

using namespace System::Xml;

XmlAttribute::XmlAttribute(XmlDocument* ownerDocument, const std::string& name)
    : XmlNode(ownerDocument), _name(XmlName("", name, "", ownerDocument))
{ }

XmlAttribute::XmlAttribute(XmlDocument* ownerDocument, const std::string& prefix, const std::string& localName, const std::string& ns)
    : XmlNode(ownerDocument), _name(XmlName(prefix, localName, ns, ownerDocument))
{ }

XmlAttribute::~XmlAttribute()
{ }

const std::string& XmlAttribute::LocalName() const
{
    return this->_name.LocalName();
}

const std::string& XmlAttribute::Name() const
{
    return this->_name.Name();
}

const std::string& XmlAttribute::NamespaceURI() const
{
    return this->_name.NamespaceURI();
}

const std::string& XmlAttribute::Prefix() const
{
    return this->_name.Prefix();
}

void XmlAttribute::SetPrefix(const std::string& prefix)
{
    this->_name = this->_name.OwnerDocument()->AddXmlName(prefix, this->LocalName(), this->NamespaceURI());
}

const XmlName& XmlAttribute::XmlNameProp() const
{
    return this->_name;
}

std::string XmlAttribute::Value()
{
    return this->InnerText();
}

void XmlAttribute::SetValue(const std::string& value)
{
    this->SetInnerText(value);
}
