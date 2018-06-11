#include "System.Xml.h"
#include "catch.hpp"

TEST_CASE("Attributes should work", "[xml]")
{
    System::Xml::XmlDocument doc;
    doc.LoadXml("<item class=\"attr value\"><name>wrench</name><length>2.4</length></item>");

    REQUIRE(doc.DocumentElement()->Attributes().Count() == 1);
}

TEST_CASE("LoadXml should work", "[xml]")
{
    System::Xml::XmlDocument doc;
    doc.LoadXml("<item><name>wrench</name></item>");

    REQUIRE(doc.DocumentElement()->LocalName() == "item");
    REQUIRE(doc.DocumentElement()->FirstChild() != nullptr);
    REQUIRE(doc.DocumentElement()->FirstChild()->LocalName() == "name");
    REQUIRE(doc.DocumentElement()->FirstChild()->InnerText() == "wrench");
}

TEST_CASE("RemoveAll should work", "[xml]")
{
    System::Xml::XmlDocument doc;
    doc.LoadXml("<item><name>wrench</name><length>2.4</length></item>");

    doc.DocumentElement()->RemoveAll();

    REQUIRE(doc.DocumentElement()->FirstChild() == nullptr);
}

TEST_CASE("LoadXML XmlNode with namespace", "[xml]")
{
    System::Xml::XmlDocument doc;
    doc.LoadXml("<ns:item><name>wrench</name><length>2.4</length></ns:item>");

    REQUIRE(doc.DocumentElement() != nullptr);
    REQUIRE(doc.DocumentElement()->Name() == "ns:item");
    REQUIRE(doc.DocumentElement()->LocalName() == "item");
}

TEST_CASE("LoadXML XmlNode with space behind localname", "[xml]")
{
    System::Xml::XmlDocument doc;
    doc.LoadXml("<item-with-space ><name>wrench</name></item-with-space >");

    REQUIRE(doc.DocumentElement() != nullptr);
    REQUIRE(doc.DocumentElement()->Name() == "item-with-space");
    REQUIRE(doc.DocumentElement()->LocalName() == "item-with-space");
}

TEST_CASE("CDATA tags should work", "[xml]")
{
    System::Xml::XmlDocument doc;
    doc.LoadXml("<item-with-cdata><![CDATA[This is data in cdata]]></item-with-cdata>");

    REQUIRE(doc.DocumentElement() != nullptr);
    REQUIRE(doc.DocumentElement()->InnerText() == "This is data in cdata");
}
