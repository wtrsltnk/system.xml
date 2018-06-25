#include <system.xml/system.xml.xmldocument.h>
#include <system.xml/system.xml.xmltext.h>

using namespace System::Xml;

XmlText::XmlText(XmlDocument *ownerDocument, const std::string &text)
    : XmlCharacterData(ownerDocument, text)
{}

XmlText::~XmlText()
{}

const std::string &XmlText::LocalName() const
{
    static std::string CommentLocalName = "#text";

    return CommentLocalName;
}

const std::string &XmlText::Name() const
{
    return this->LocalName();
}
