#ifndef _STD_XMLSTREAM_H_
#define _STD_XMLSTREAM_H_

#include <string>
#include <map>
#include <stack>
#include <fstream>

class xmlelement
{
};

class xmlstream
{
    std::ifstream _is;
    std::string _namespace;
    std::string _name;
    std::string _value;
    std::map<std::string,std::string> _attributes;
    std::stack<std::string> _path;
public:
    xmlstream() { }
    xmlstream(const std::string& __s) { this->open(__s); }
    virtual ~xmlstream() { this->close(); }

    bool open(const std::string& __s)
    {
        this->_is.open(__s.c_str(), std::ios_base::in);
        return this->_is.is_open();
    }

    void close()
    {
        if (this->_is.is_open())
        {
            this->_is.close();
        }
    }

    bool move_to_first_child();
    bool move_to_first_child_with_name(const std::string& __n)
    {
        if (this->move_to_first_child())
        {
            while (this->_name != __n)
            {
                if (!this->move_to_next_sibling()) return false;
            }

            return (this->_name != __n);
        }
        return false;
    }

    bool move_to_next_sibling();
    bool move_to_next_sibling_with_name(const std::string& __n)
    {
        do
        {
            if (!this->move_to_next_sibling()) return false;
        }
        while (this->_name != __n);
        return (this->_name != __n);
    }

    bool move_to_path(const std::string& __p);

    const std::string& current_namespace() const { return this->_namespace; }
    const std::string& current_name() const { return this->_name; }
    const std::string& current_value() const { return this->_value; }
    const std::map<std::string,std::string>& current_attributes() const { return this->_attributes; }
    const std::stack<std::string>& current_path() const { return this->_path; }

};

#endif // _STD_XMLSTREAM_H_
