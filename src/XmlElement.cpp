#include <system.xml/XmlDocument.h>
#include <system.xml/XmlElement.h>

using namespace System::Xml;

XmlElement::XmlElement(XmlDocument *ownerDocument, const std::string &name)
    : XmlLinkedNode(ownerDocument), _name(XmlName("", name, "", ownerDocument))
{}

XmlElement::XmlElement(XmlDocument *ownerDocument, const std::string &prefix, const std::string &localName, const std::string &ns)
    : XmlLinkedNode(ownerDocument), _name(XmlName(prefix, localName, ns, ownerDocument))
{}

XmlElement::~XmlElement()
{}

const std::string &XmlElement::LocalName() const
{
    return this->_name.LocalName();
}

const std::string &XmlElement::Name() const
{
    return this->_name.Name();
}

const std::string &XmlElement::NamespaceURI() const
{
    return this->_name.NamespaceURI();
}

const std::string &XmlElement::Prefix() const
{
    return this->_name.Prefix();
}

void XmlElement::SetPrefix(const std::string &prefix)
{
    this->_name = this->_name.OwnerDocument()->AddXmlName(prefix, this->LocalName(), this->NamespaceURI());
}

const XmlName &XmlElement::XmlNameProp() const
{
    return this->_name;
}
