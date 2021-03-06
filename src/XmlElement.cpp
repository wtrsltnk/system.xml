#include <system.xml/system.xml.document.h>
#include <system.xml/system.xml.element.h>

using namespace System::Xml;

XmlElement::XmlElement(XmlDocument *ownerDocument, const std::string &localName)
    : XmlLinkedNode(ownerDocument), _name(ownerDocument->AddXmlName("", localName, ""))
{}

XmlElement::XmlElement(XmlDocument *ownerDocument, const std::string &prefix, const std::string &localName, const std::string &ns)
    : XmlLinkedNode(ownerDocument), _name(ownerDocument->AddXmlName(prefix, localName, ns))
{}

XmlElement::~XmlElement()
{}

const std::string &XmlElement::LocalName() const
{
    return this->_name->LocalName();
}

const std::string &XmlElement::Name() const
{
    return this->_name->Name();
}

const std::string &XmlElement::NamespaceURI() const
{
    return this->_name->NamespaceURI();
}

const std::string &XmlElement::Prefix() const
{
    return this->_name->Prefix();
}

void XmlElement::SetPrefix(const std::string &prefix)
{
    this->_name = this->_name->OwnerDocument()->AddXmlName(prefix, this->LocalName(), this->NamespaceURI());
}

const XmlName *XmlElement::XmlNameProp() const
{
    return this->_name;
}
