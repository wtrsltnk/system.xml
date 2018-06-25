#include <system.xml/system.xml.document.h>
#include <system.xml/system.xml.text.h>

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
