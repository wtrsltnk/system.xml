#ifndef XMLLOADER_H
#define XMLLOADER_H

#include <XmlDocument.h>
#include <XmlAttributeCollection.h>
#include <istream>
#include <string>
#include <map>

namespace System
{
namespace Xml
{

class XmlLoader
{
public:
    XmlLoader();
    virtual ~XmlLoader();

    void ResetNamespaces();
    void Load(XmlDocument& doc, std::istream& fr);

private:
    bool ParseTag(const char*& ptr, const char* open, const char* close, std::string& output);
    void ParseTagName(const std::string& str, std::string& prefix, std::string& localname);
    void ParseAttributes(const std::string& str, XmlDocument& doc, XmlAttributeCollection& attrs);
    std::string ParseNamespaceURI(const std::string& prefix);

    std::string _currentDefaultNamespace;
    std::map<std::string, std::string> _namespaces;
};

}
}

#endif // XMLLOADER_H
