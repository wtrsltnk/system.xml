#include <XmlDocumentType.h>
#include <XmlDocument.h>

using namespace System::Xml;

XmlDocumentType::XmlDocumentType(XmlDocument* ownerDocument, const std::string& name, const std::string& publicId, const std::string& systemId, const std::string& internalSubset)
    : XmlLinkedNode(ownerDocument), _name(name), _publicId(publicId), _systemId(systemId), _internalSubset(internalSubset)
{ }

XmlDocumentType::~XmlDocumentType()
{
    this->RemoveAll();
}

const std::string& XmlDocumentType::InternalSubset()
{
    return this->_internalSubset;
}

const std::string& XmlDocumentType::LocalName() const
{
    return this->_name;
}

const std::string& XmlDocumentType::Name() const
{
    return this->_name;
}

const std::string& XmlDocumentType::NamespaceURI() const
{
    static std::string XmlDocumentTypeNamespaceURI = "";

    return XmlDocumentTypeNamespaceURI;
}

const std::string& XmlDocumentType::Prefix() const
{
    static std::string XmlDocumentTypePrefix = "";

    return XmlDocumentTypePrefix;
}

void XmlDocumentType::SetPrefix(const std::string& prefix)
{ }

const std::string& XmlDocumentType::PublicId()
{
    return this->_publicId;
}

const std::string& XmlDocumentType::SystemId()
{
    return this->_systemId;
}
