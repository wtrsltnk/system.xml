#include <xml/XmlDocument.h>
#include <xml/XmlNodeList.h>

using namespace System::Xml;

XmlNodeList::XmlNodeList()
{}

XmlNodeList::XmlNodeList(XmlNode *node)
{
    XmlNode *itr = node->FirstChild();

    if (itr != 0)
    {
        do
        {
            this->push_back(itr);
            itr = itr->NextSibling();
        } while (itr != 0 && itr != node->FirstChild());
    }
}

XmlNodeList::~XmlNodeList()
{}

int XmlNodeList::Count()
{
    return int(this->size());
}

XmlNode *XmlNodeList::operator[](int index)
{
    return this->Item(index);
}

XmlNode *XmlNodeList::Item(int index)
{
    if (index >= 0 && index < this->Count())
        return this->at(index);

    return 0;
}
