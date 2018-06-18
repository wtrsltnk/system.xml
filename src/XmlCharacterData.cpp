#include <system.xml/XmlCharacterData.h>
#include <system.xml/XmlDocument.h>

using namespace System::Xml;

XmlCharacterData::XmlCharacterData(XmlDocument *ownerDocument)
    : XmlLinkedNode(ownerDocument)
{}

XmlCharacterData::XmlCharacterData(XmlDocument *ownerDocument, const std::string &text)
    : XmlLinkedNode(ownerDocument), _data(text)
{}

XmlCharacterData::~XmlCharacterData()
{}

std::string XmlCharacterData::Data()
{
    return this->_data;
}

std::string XmlCharacterData::InnerText()
{
    return this->_data;
}

void XmlCharacterData::SetInnerText(const std::string &innerText)
{
    this->_data = innerText;
}

int XmlCharacterData::Length()
{
    return int(this->_data.size());
}

const std::string &XmlCharacterData::NamespaceURI() const
{
    static std::string XmlCharacterDataNamespaceURI = "";

    return XmlCharacterDataNamespaceURI;
}

void XmlCharacterData::SetNamespaceURI(const std::string & /*namespaceURI*/)
{}

std::string XmlCharacterData::Value()
{
    return this->_data;
}

void XmlCharacterData::SetValue(const std::string &value)
{
    this->_data = value;
}

const std::string &XmlCharacterData::Prefix() const
{
    static std::string XmlCharacterDataPrefix = "";

    return XmlCharacterDataPrefix;
}

void XmlCharacterData::SetPrefix(const std::string &prefix)
{}
