#include <xml/XmlComment.h>
#include <xml/XmlDocument.h>

using namespace System::Xml;

XmlComment::XmlComment(XmlDocument *ownerDocument, const std::string &text)
    : XmlCharacterData(ownerDocument, text)
{}

XmlComment::~XmlComment()
{}

const std::string &XmlComment::LocalName() const
{
    static std::string CommentLocalName = "#comment";

    return CommentLocalName;
}

const std::string &XmlComment::Name() const
{
    return this->LocalName();
}
