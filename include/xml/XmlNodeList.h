#ifndef XMLNODELIST_H
#define XMLNODELIST_H

#include <vector>

namespace System {
namespace Xml {

class XmlNodeList : std::vector<class XmlNode *>
{
    friend class XmlNode; // This makes iterating over this std::vector easier
public:
    XmlNodeList();
    XmlNodeList(class XmlNode *node);
    virtual ~XmlNodeList();

    // Properties
public:
    // Gets the number of nodes in the XmlNodeList.
    int Count();

    // Gets a node at the given index.
    class XmlNode *operator[](int index);

    // Methods
public:
    // Retrieves a node at the given index.
    class XmlNode *Item(int index);
};

} // namespace Xml
} // namespace System

#endif // XMLNODELIST_H
