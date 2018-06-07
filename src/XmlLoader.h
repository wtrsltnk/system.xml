#ifndef XMLLOADER_H
#define XMLLOADER_H

#include <xml/XmlDocument.h>
#include <xml/XmlAttributeCollection.h>
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
    bool ParseTag(char const *& ptr, char const *open, char const *close, std::string &output);
    void ParseTagName(std::string &str, std::string &prefix, std::string &localname);
    void ParseAttributes(std::string &str, XmlDocument& doc, XmlAttributeCollection& attrs);
    std::string ParseNamespaceURI(const std::string &prefix);

    std::string _currentDefaultNamespace;
    std::map<std::string, std::string> _namespaces;
};

}
}

#endif // XMLLOADER_H
