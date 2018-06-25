#include <system.xml/system.xml.xmlcdatasection.h>
#include <system.xml/system.xml.xmldocument.h>

using namespace System::Xml;

XmlCDataSection::XmlCDataSection(XmlDocument *ownerDocument, const std::string &text)
    : XmlCharacterData(ownerDocument, text)
{}

XmlCDataSection::~XmlCDataSection()
{}

const std::string &XmlCDataSection::LocalName() const
{
    static std::string CDataSectionLocalName = "#cdata-section";

    return CDataSectionLocalName;
}

const std::string &XmlCDataSection::Name() const
{
    return this->LocalName();
}
