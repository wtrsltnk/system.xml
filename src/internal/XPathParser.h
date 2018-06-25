#ifndef XPATHPARSER_H
#define XPATHPARSER_H

#include <string>
#include "XPathScanner.h"

namespace internal {
namespace Xml {
namespace XPath {

class XPathParser
{
    XPathScanner &_scanner;
public:
    XPathParser(XPathScanner &scanner);
    virtual ~XPathParser();
};

} // namespace XPath
} // namespace Xml
} // namespace internal

#endif // XPATHPARSER_H
