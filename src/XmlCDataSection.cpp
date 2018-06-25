#include <system.xml/system.xml.cdatasection.h>
#include <system.xml/system.xml.document.h>

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
