#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <XmlDocument.h>
#include <XmlNode.h>
#include <sstream>

namespace System
{
namespace Xml
{

class XmlWriter
{
public:
    XmlWriter();
    virtual ~XmlWriter();

    std::string Write(XmlDocument& doc);

private:
    void WriteNode(XmlNode* node, std::stringstream& result, int depth);
};

}
}

#endif // XMLWRITER_H