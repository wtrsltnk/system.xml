#include <system.xml/system.xml.xmldocument.h>
#include <system.xml/system.xml.xmlprocessinginstruction.h>

using namespace System::Xml;

XmlProcessingInstruction::XmlProcessingInstruction(const std::string &target, const std::string &data, XmlDocument *ownerDocument)
    : XmlLinkedNode(ownerDocument), _target(target), _data(data)
{}

XmlProcessingInstruction::~XmlProcessingInstruction()
{}

const std::string &XmlProcessingInstruction::Data() const
{
    return this->_data;
}

void XmlProcessingInstruction::SetData(const std::string &data)
{
    this->_data = data;
}

std::string XmlProcessingInstruction::InnerText()
{
    return this->_data;
}

void XmlProcessingInstruction::SetInnerText(const std::string &innerText)
{
    this->_data = innerText;
}

const std::string &XmlProcessingInstruction::LocalName() const
{
    return this->Name();
}

const std::string &XmlProcessingInstruction::Name() const
{
    return this->_target;
}

const std::string &XmlProcessingInstruction::Target() const
{
    return this->_target;
}

const std::string &XmlProcessingInstruction::NamespaceURI() const
{
    static std::string XmlProcessingInstructionNamespaaceURI = "";

    return XmlProcessingInstructionNamespaaceURI;
}

void XmlProcessingInstruction::SetNamespaceURI(const std::string &namespaceURI)
{}

std::string XmlProcessingInstruction::Value()
{
    return this->_data;
}

void XmlProcessingInstruction::SetValue(const std::string &value)
{
    this->_data = value;
}

const std::string &XmlProcessingInstruction::Prefix() const
{
    static std::string XmlProcessingInstructionPrefix = "";

    return XmlProcessingInstructionPrefix;
}

void XmlProcessingInstruction::SetPrefix(const std::string &prefix)
{}
