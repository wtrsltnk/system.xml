#include <xml/XmlAttributeCollection.h>
#include <xml/XmlDocument.h>

using namespace System::Xml;

XmlAttributeCollection::XmlAttributeCollection()
{}

XmlAttributeCollection::~XmlAttributeCollection()
{}

int XmlAttributeCollection::Count()
{
    return int(this->size());
}

XmlAttribute *XmlAttributeCollection::operator[](const std::string &key)
{
    return this->Item(key);
}

XmlAttribute *XmlAttributeCollection::operator[](int index)
{
    return this->ItemAt(index);
}

XmlAttribute *XmlAttributeCollection::Append(XmlAttribute *node)
{
    this->insert(std::make_pair(node->Name(), node));
    return node;
}

XmlAttribute *XmlAttributeCollection::Item(const std::string &key)
{
    if (this->find(key) != this->end())
        return this->at(key);

    return 0;
}

XmlAttribute *XmlAttributeCollection::ItemAt(int index)
{
    XmlAttributeCollection::iterator itr = this->begin();

    for (int i = 0; i < index; i++, ++itr)
        ;

    return itr->second;
}

void XmlAttributeCollection::RemoveAll()
{
    std::map<std::string, XmlAttribute *>::iterator itr = this->begin();
    while (itr != this->end())
    {
        delete itr->second;
        this->erase(itr++);
    }
}

void XmlAttributeCollection::RemoveNamedItem(const std::string &name)
{}

void XmlAttributeCollection::RemoveNamedItem(const std::string &localName, const std::string &namespaceURI)
{}
