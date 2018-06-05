#include "catch.hpp"
#include "xml.h"

TEST_CASE("Attributes should work", "[xml]")
{
    auto doc = System::Xml::XmlDocument();
    doc.LoadXml("<item class=\"attr value\"><name>wrench</name><length>2.4</length></item>");
    
    REQUIRE(doc.DocumentElement()->Attributes().Count() == 1);
}

TEST_CASE("LoadXml should work", "[xml]")
{
    auto doc = System::Xml::XmlDocument();
    doc.LoadXml("<item><name>wrench</name></item>");
    
    REQUIRE(doc.DocumentElement()->LocalName() == "item");
    REQUIRE(doc.DocumentElement()->FirstChild() != nullptr);
    REQUIRE(doc.DocumentElement()->FirstChild()->LocalName() == "name");
    REQUIRE(doc.DocumentElement()->FirstChild()->InnerText() == "wrench");
}

TEST_CASE("RemoveAll should work", "[xml]")
{
    auto doc = System::Xml::XmlDocument();
    doc.LoadXml("<item><name>wrench</name><length>2.4</length></item>");
    
    doc.DocumentElement()->RemoveAll();

    REQUIRE(doc.DocumentElement()->FirstChild() == nullptr);
}
