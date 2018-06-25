
add_library(system.xml
    XmlAttribute.cpp
    XmlAttributeCollection.cpp
    XmlCDataSection.cpp
    XmlCharacterData.cpp
    XmlComment.cpp
    XmlDocument.cpp
    XmlDocumentType.cpp
    XmlElement.cpp
    XmlException.cpp
    XmlLinkedNode.cpp
    XmlLoader.cpp
    XmlLoader.h
    XmlName.cpp
    XmlNameTable.cpp
    XmlNode.cpp
    XmlNodeList.cpp
    XmlProcessingInstruction.cpp
    XmlText.cpp
    XmlWriter.cpp
    XmlWriter.h
    internal/XPathParser.cpp
    internal/XPathScanner.cpp
    )

target_include_directories(system.xml
    PUBLIC
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ../include
    )

target_compile_features(system.xml
    PRIVATE cxx_auto_type
    PRIVATE cxx_nullptr
    PRIVATE cxx_range_for
    )

install(
    TARGETS
        system.xml
    EXPORT
        system.xml
    DESTINATION
        "lib"
    )

install(
    FILES
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlattribute.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlattributecollection.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlcdatasection.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlcharacterdata.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlcomment.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmldocument.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmldocumenttype.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlduplicateattributesfoundexception.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlelement.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlexception.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmllinkednode.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlname.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlnametable.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlnode.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlnodelist.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlnodetype.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlprocessinginstruction.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmltext.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlundefinednamespacefoundexception.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlunexpectedcharacterexception.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlunexpectedclosingtagexception.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.xmlunexpectedendoffileexception.h
    DESTINATION
        "include/system.xml"
    )

install(
    EXPORT
        system.xml
    FILE
        system.xml-config.cmake
    DESTINATION
        "cmake"
    )
