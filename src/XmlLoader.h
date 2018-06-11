#ifndef XMLLOADER_H
#define XMLLOADER_H

#include <istream>
#include <map>
#include <string>
#include <xml/XmlAttributeCollection.h>
#include <xml/XmlDocument.h>

namespace System {
namespace Xml {

class XmlLoader
{
public:
    XmlLoader();
    virtual ~XmlLoader();

    void ResetNamespaces();
    void Load(XmlDocument &doc, std::istream &fr);

    static char const *XmlPrefixNamespace;
    static char const *XmlnsPrefixNamespace;

private:
    std::string _currentDefaultNamespace;
    std::map<std::string, std::string> _namespaces;

    void parseEntityDeclaration(XmlNode *node, std::istream &fr);
    void parseTextDeclaration(XmlNode *node, std::istream &fr);
    XmlNode *createNode(XmlNode *currentNode, std::string const &tagName, std::map<std::string, std::string> const &attrs);
    XmlAttribute *createAttribute(XmlNode *currentNode, std::string const &key, std::string const &val);
};

} // namespace Xml
} // namespace System

#endif // XMLLOADER_H
