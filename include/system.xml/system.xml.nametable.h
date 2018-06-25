#ifndef _SYSTEM_XML_NAMETABLE_H_
#define _SYSTEM_XML_NAMETABLE_H_

#include <string>

namespace System {
namespace Xml {

class XmlNameTable
{
public:
    XmlNameTable();
    virtual ~XmlNameTable();

public: // Methods
    // When overridden in a derived class, atomizes the specified string and adds it to the XmlNameTable.
    std::string Add(char const array[], int offset, int length);

    // When overridden in a derived class, atomizes the specified string and adds it to the XmlNameTable.
    std::string Add(std::string const &array);

    // Determines whether the specified object is equal to the current object.(Inherited from Object.)
    //System_CAPS_pubmethod	Equals(Object)

    // Allows an object to try to free resources and perform other cleanup operations before it is reclaimed by garbage collection.(Inherited from Object.)
    //System_CAPS_protmethod	Finalize()

    // When overridden in a derived class, gets the atomized string containing the same characters as the specified range of characters in the given array.
    std::string Get(char const array[], int offset, int length);

    // When overridden in a derived class, gets the atomized string containing the same value as the specified string.
    std::string Get(std::string const &array);

    // Serves as the default hash function. (Inherited from Object.)
    //System_CAPS_pubmethod	GetHashCode()

    // Gets the Type of the current instance.(Inherited from Object.)
    //System_CAPS_pubmethod	GetType()

    // Creates a shallow copy of the current Object.(Inherited from Object.)
    //System_CAPS_protmethod	MemberwiseClone()

    // Returns a string that represents the current object.(Inherited from Object.)
    //System_CAPS_pubmethod	ToString()
};

} // namespace Xml
} // namespace System

#endif // _SYSTEM_XML_NAMETABLE_H_
