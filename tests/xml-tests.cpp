#include "catch.hpp"
#include "xml.h"

TEST_CASE("LoadXml should work", "[xml]")
{
    auto doc = System::Xml::XmlDocument();
    doc.LoadXml("<item><name>wrench</name></item>");
    
    REQUIRE(doc.DocumentElement()->LocalName() == "item");
    REQUIRE(doc.DocumentElement()->FirstChild() != nullptr);
    REQUIRE(doc.DocumentElement()->FirstChild()->LocalName() == "name");
    REQUIRE(doc.DocumentElement()->FirstChild()->InnerText() == "wrench");
}