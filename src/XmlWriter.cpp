#include "XmlWriter.h"
#include <algorithm>

using namespace System::Xml;

XmlWriter::XmlWriter()
{ }

XmlWriter::~XmlWriter()
{ }

std::string XmlWriter::Write(XmlDocument& doc)
{
    std::stringstream result;

    XmlNodeList children = doc.ChildNodes();
    for (int i = 0; i < children.Count(); i++)
        this->WriteNode(children[i], result, 0);

    return result.str();
}

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

void XmlWriter::WriteNode(XmlNode* node, std::stringstream& result, int depth)
{
    if (node->NodeType() == XmlNodeType::Element)
    {
        XmlNodeList children = node->ChildNodes();
        XmlAttributeCollection attrs = node->Attributes();
        bool compact = children.Count() == 1 && children[0]->NodeType() == XmlNodeType::Text;

        result << std::endl;
        for (int i = 0; i < depth; i++)
            result << "\t";
        result << "<" << node->Name();
        for (int i = 0; i < attrs.Count(); i++)
            result << " " << attrs.ItemAt(i)->Name() << "=\"" << attrs.ItemAt(i)->Value() << "\"";
        if (children.Count() == 0)
        {
            result<< " />";
        }
        else
        {
            result<< ">";

            for (int i = 0; i < children.Count(); i++)
                this->WriteNode(children[i], result, depth + 1);

            if (compact == false)
            {
                result << std::endl;
                for (int i = 0; i < depth; i++)
                    result << "\t";
            }
            result << "</" << node->Name() << ">";
        }
    }
    else if (node->NodeType() == XmlNodeType::CDATA)
    {
        for (int i = 0; i < depth; i++)
            result << "\t";
        result << "<![CDATA[" << node->Value() << "]]>";
    }
    else if (node->NodeType() == XmlNodeType::Comment)
    {
        result << std::endl;
        for (int i = 0; i < depth; i++)
            result << "\t";
        result << "<!--" << node->Value() << "-->";
    }
    else if (node->NodeType() == XmlNodeType::ProcessingInstruction)
    {
        XmlAttributeCollection attrs = node->Attributes();

        result << std::endl;
        for (int i = 0; i < depth; i++)
            result << "\t";
        result << "<?" << node->Name();
        for (int i = 0; i < attrs.Count(); i++)
            result << " " << attrs.ItemAt(i)->Name() << "=\"" << attrs.ItemAt(i)->Value() << "\"";
        result << " ?>";
    }
    else if (node->NodeType() == XmlNodeType::DocumentType)
    {
        XmlDocumentType* docType = (XmlDocumentType*)node;
        result << std::endl;
        for (int i = 0; i < depth; i++)
            result << "\t";
        result << "<!DOCTYPE " << node->Name();
        if (docType->PublicId() != "")
            result << " PUBLIC " << docType->PublicId();
        else if (docType->SystemId() != "")
            result << " SYSTEM " << docType->SystemId();
        result << ">";
    }
    else if (node->NodeType() == XmlNodeType::Text)
    {
        std::string val = node->Value();
        trim(val);
        if (val != "")
            result << val;
    }
}