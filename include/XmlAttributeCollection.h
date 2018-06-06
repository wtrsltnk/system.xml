#ifndef XMLATTRIBUTECOLLECTION_H
#define XMLATTRIBUTECOLLECTION_H

#include <map>
#include <string>

namespace System
{
namespace Xml
{

class XmlAttributeCollection : std::map<std::string, class XmlAttribute*>
{
    friend class XmlNode;   // This makes iterating over this std::map easier
protected:
public:
    XmlAttributeCollection();
    virtual ~XmlAttributeCollection();

    // Properties
public:
    // Gets the number of nodes in the XmlNodeList.
    int Count();

    // Gets a node at the given key.
    XmlAttribute* operator[](const std::string& key);

    // Gets a node at the given index.
    XmlAttribute* operator[](int index);

    // Methods
public:
    // Inserts the specified attribute as the last node in the collection.
    XmlAttribute* Append(XmlAttribute* node);

    // Retrieves a node at the given key.
    class XmlAttribute* Item(const std::string& key);

    // Retrieves a node at the given index.
    class XmlAttribute* ItemAt(int index);

    // Removes all attributes from the collection.
    void RemoveAll();

    // Removes the node from the XmlAttributeCollection.
    void RemoveNamedItem(const std::string& name);

    // Removes the node from the XmlAttributeCollection.
    void RemoveNamedItem(const std::string& localName, const std::string& namespaceURI);

};

}
}

#endif // XMLATTRIBUTECOLLECTION_H
