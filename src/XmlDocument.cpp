#include "XmlLoader.h"
#include <fstream>
#include <sstream>
#include <system.xml/system.xml.document.h>

using namespace System::Xml;

XmlDocument::XmlDocument()
    : XmlNode(this)
{}

XmlDocument::~XmlDocument()
{
    while (!_nameTable.empty())
    {
        auto name = _nameTable.back();
        _nameTable.pop_back();
        delete name;
    }
}

XmlElement *XmlDocument::DocumentElement()
{
    return (XmlElement *)this->FindChild(XmlNodeType::Element);
}

const std::string &XmlDocument::LocalName() const
{
    static std::string documentLocalName = "#document";

    return documentLocalName;
}

const std::string &XmlDocument::Name() const
{
    return this->LocalName();
}

const std::string &XmlDocument::NamespaceURI() const
{
    static std::string documentNamespaceURI = "";

    return documentNamespaceURI;
}

const std::string &XmlDocument::Prefix() const
{
    static std::string documentPrefix = "";

    return documentPrefix;
}

void XmlDocument::SetPrefix(const std::string &prefix)
{}

XmlAttribute *XmlDocument::CreateAttribute(const std::string &name)
{
    return new XmlAttribute(this, "", name, "");
}

XmlAttribute *XmlDocument::CreateAttribute(const std::string &name, const std::string &namespaceURI)
{
    return new XmlAttribute(this, "", name, namespaceURI);
}

XmlAttribute *XmlDocument::CreateAttribute(const std::string &prefix, const std::string &localName, const std::string &namespaceURI)
{
    return new XmlAttribute(this, prefix, localName, namespaceURI);
}

XmlCDataSection *XmlDocument::CreateCDataSection(const std::string &text)
{
    return new XmlCDataSection(this, text);
}

XmlComment *XmlDocument::CreateComment(const std::string &text)
{
    return new XmlComment(this, text);
}

XmlDocumentType *XmlDocument::CreateDocumentType(const std::string &name, const std::string &publicId, const std::string &systemId, const std::string &internalSubset)
{
    return new XmlDocumentType(this, name, publicId, systemId, internalSubset);
}

XmlElement *XmlDocument::CreateElement(const std::string &name)
{
    return new XmlElement(this, name);
}

XmlElement *XmlDocument::CreateElement(const std::string &name, const std::string &namespaceURI)
{
    return new XmlElement(this, "", name, namespaceURI);
}

XmlElement *XmlDocument::CreateElement(const std::string &prefix, const std::string &localName, const std::string &namespaceURI)
{
    return new XmlElement(this, prefix, localName, namespaceURI);
}

XmlProcessingInstruction *XmlDocument::CreateProcessingInstruction(const std::string &target, const std::string &data)
{
    return new XmlProcessingInstruction(target, data, this);
}

XmlText *XmlDocument::CreateTextNode(const std::string &text)
{
    return new XmlText(this, text);
}

XmlName *XmlDocument::AddXmlName(const std::string &prefix, const std::string &localName, const std::string &ns)
{
    for (auto name : _nameTable)
    {
        if (name->LocalName() != localName) continue;
        if (name->Prefix() != prefix) continue;
        if (name->NamespaceURI() != ns) continue;

        return name;
    }

    auto newName = new XmlName(prefix, localName, ns, this);
    _nameTable.push_back(newName);
    return newName;
}

#include <iostream>

void XmlDocument::Load(const std::string &filename)
{
    std::ifstream file(filename);

    if (file.is_open())
    {
        XmlLoader loader;
        loader.Load(*this, file);
    }
    else
    {
        std::cout << "load failed/n/n";
    }
}

void XmlDocument::LoadXml(const std::string &xml)
{
    std::stringstream ss(xml);
    XmlLoader loader;
    loader.Load(*this, ss);
}
