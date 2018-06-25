#ifndef XPATHSCANNER_H
#define XPATHSCANNER_H

#include <string>

namespace internal {
namespace Xml {
namespace XPath {

class XPathScanner
{
public:
    XPathScanner(std::string const &expression);
    virtual ~XPathScanner();
};

} // namespace XPath
} // namespace Xml
} // namespace internal

#endif // XPATHSCANNER_H
