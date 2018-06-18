#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <sstream>
#include <system.xml/XmlDocument.h>
#include <system.xml/XmlNode.h>

namespace System {
namespace Xml {

class XmlWriter
{
public:
    XmlWriter();
    virtual ~XmlWriter();

    std::string Write(XmlDocument &doc);

private:
    void WriteNode(XmlNode *node, std::stringstream &result, int depth);
};

} // namespace Xml
} // namespace System

#endif // XMLWRITER_H
