#include "XmlLoader.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <locale>
#include <xml/XmlDuplicateAttributesFoundException.h>
#include <xml/XmlUndefinedNamespaceFoundException.h>
#include <xml/XmlUnexpectedCharacterException.h>
#include <xml/XmlUnexpectedClosingTagException.h>
#include <xml/XmlUnexpectedEndOfFileException.h>

using namespace System::Xml;

XmlLoader::XmlLoader()
{
}

XmlLoader::~XmlLoader()
{
}

char const *XmlLoader::XmlPrefixNamespace = "http://www.w3.org/XML/1998/namespace";
char const *XmlLoader::XmlnsPrefixNamespace = "http://www.w3.org/2000/xmlns/";

void XmlLoader::ResetNamespaces()
{
    this->_currentDefaultNamespace = "";
    this->_namespaces.clear();
    this->_namespaces.insert(std::make_pair("xml", XmlPrefixNamespace));
    this->_namespaces.insert(std::make_pair("xmlns", XmlnsPrefixNamespace));
}

void checkUnexpectedEnd(char c)
{
    if (c == '\0')
    {
        throw XmlUnexpectedEndOfFileException();
    }
}

void checkUnexpectedCharacter(char c, char expected)
{
    if (c != expected)
    {
        throw XmlUnexpectedCharacterException(c, expected);
    }
}

char skipSpaces(std::istream &fr)
{
    char c = fr.get();

    // Skip all spaces until we reach '>' or an attribute
    while (c <= ' ')
    {
        checkUnexpectedEnd(c);
        c = fr.get();
    }

    return c;
}

std::string parseTagName(std::istream &fr)
{
    std::string data;

    char c;
    while (fr.peek() > ' ' && fr.peek() != '>')
    {
        c = fr.get();
        checkUnexpectedEnd(c);

        data += c;
    }

    return data;
}

std::map<std::string, std::string> parseAttributes(std::istream &fr)
{
    std::map<std::string, std::string> attrs;

    char c = skipSpaces(fr);

    while (c != '>')
    {
        checkUnexpectedEnd(c);
        // Skip all spaces until we reach '>' or an attribute

        std::string key;
        while (c != '=')
        {
            checkUnexpectedEnd(c);
            if (c > ' ')
            {
                key += c;
            }
            c = fr.get();
        }

        if (attrs.find(key) != attrs.end())
        {
            throw XmlDuplicateAttributesFoundException();
        }

        std::string val;
        c = fr.get();
        if (c == '\"')
        {
            c = fr.get();
            while (c != '\"')
            {
                checkUnexpectedEnd(c);
                val += c;
                c = fr.get();
            }
        }
        else
        {
            while (c > ' ' && c != '>')
            {
                checkUnexpectedEnd(c);
                val += c;
                c = fr.get();
            }
        }
        checkUnexpectedEnd(c);

        attrs.insert(std::make_pair(key, val));

        c = skipSpaces(fr);
    }

    return attrs;
}

void expectedTextOrThrow(std::istream &fr, std::string const &text)
{
    for (auto e : text)
    {
        char c = fr.get();
        if (e != c)
        {
            throw XmlUnexpectedCharacterException(c, e);
        }
    }
}

bool endsWith(std::string const &subject, std::string const &end)
{
    if (subject.find(end) != std::string::npos)
    {
        return subject.find(end) == (subject.size() - end.size());
    }

    return false;
}

std::string getDataUntil(std::istream &fr, std::string const &text)
{
    bool atEnd = false;
    char c = fr.get();
    std::string data;

    while (!atEnd)
    {
        checkUnexpectedEnd(c);
        data += c;
        if (endsWith(data, text))
        {
            atEnd = true;
            break;
        }
        c = fr.get();
    }

    return data.substr(0, data.size() - text.size());
}

void XmlLoader::Load(XmlDocument &doc, std::istream &fr)
{
    char c = fr.get();
    std::string data;
    XmlNode *node = &doc;

    while (!fr.eof())
    {
        if (c == '<')
        {
            if (data.size() > 0)
            {
                auto textNode = node->OwnerDocument()->CreateTextNode(data);
                node->AppendChild(textNode);
                data = "";
            }

            if (fr.peek() == '!') // This is a entity declaration
            {
                parseEntityDeclaration(node, fr);
            }
            else if (fr.peek() == '?') // This is a text declaration
            {
                parseTextDeclaration(node, fr);
            }
            else if (fr.peek() == '/') // This is an end tag
            {
                fr.get();
                auto tagName = parseTagName(fr);
                if (node->Name() != tagName)
                {
                    throw XmlUnexpectedClosingTagException();
                }
                c = skipSpaces(fr);
                if (c != '>')
                {
                    throw XmlUnexpectedCharacterException(c, '>');
                }
                node = node->ParentNode();
            }
            else // This is a start tag
            {
                auto tagName = parseTagName(fr);
                auto attributes = parseAttributes(fr);

                node = createNode(node, tagName, attributes);
            }
        }
        else
        {
            data += c;
        }

        c = fr.get();
    }
}

XmlNode *XmlLoader::createNode(XmlNode *currentNode, std::string const &tagName, std::map<std::string, std::string> const &attrs)
{
    XmlNode *newNode = nullptr;

    if (tagName.find_first_of(':') == std::string::npos)
    {
        newNode = currentNode->OwnerDocument()->CreateElement(tagName);
    }
    else
    {
        std::string prefix = tagName.substr(0, tagName.find_first_of(':'));
        std::string localName = tagName.substr(tagName.find_first_of(':') + 1);
        newNode = currentNode->OwnerDocument()->CreateElement(prefix, localName, "");
    }

    for (auto attr : attrs)
    {
        createAttribute(newNode, attr.first, attr.second);
    }

    currentNode->AppendChild(newNode);

    return newNode;
}

XmlAttribute *XmlLoader::createAttribute(XmlNode *currentNode, std::string const &key, std::string const &val)
{
    XmlAttribute *attr = nullptr;

    if (key.find_first_of(':') == std::string::npos)
    {
        attr = currentNode->OwnerDocument()->CreateAttribute(key);
    }
    else
    {
        std::string prefix = key.substr(0, key.find_first_of(':'));
        std::string localName = key.substr(key.find_first_of(':') + 1);
        attr = currentNode->OwnerDocument()->CreateAttribute(prefix, localName, "");
    }

    attr->SetValue(val);
    currentNode->Attributes().Append(attr);

    return attr;
}

void XmlLoader::parseEntityDeclaration(XmlNode *node, std::istream &fr)
{
    std::string data;

    char c = fr.get();
    if (c != '!')
    {
        throw XmlUnexpectedCharacterException(c, '!');
    }

    if (fr.peek() == '-') // This is a comment
    {
        expectedTextOrThrow(fr, "--");
        data = getDataUntil(fr, "-->");
        node->AppendChild(
            node->OwnerDocument()
                ->CreateComment(data));
        return;
    }

    if (fr.peek() == '[')
    {
        expectedTextOrThrow(fr, "[CDATA[");
        data = getDataUntil(fr, "]]>");
        node->AppendChild(
            node->OwnerDocument()
                ->CreateCDataSection(data));
    }
}

void XmlLoader::parseTextDeclaration(XmlNode *node, std::istream &fr)
{
    char c = fr.get();
    if (c != '?')
    {
        throw XmlUnexpectedCharacterException(c, '?');
    }

    c = fr.get();

    // for now we skip this completely
    while (c != '?' && fr.peek() != '>')
    {
        checkUnexpectedEnd(c);
        if (c == '?')
        {
            throw XmlException("Unexpected character found, expected '?>' but missing '>'");
        }
        if (c == '>')
        {
            throw XmlException("Unexpected character found, expected '?>' but missing '?'");
        }
        c = fr.get();
    }
    c = fr.get();
    checkUnexpectedCharacter(c, '>');
}
