
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
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.attribute.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.attributecollection.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.cdatasection.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.characterdata.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.comment.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.document.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.documenttype.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.duplicateattributesfoundexception.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.element.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.exception.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.linkednode.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.name.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.nametable.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.node.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.nodelist.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.nodetype.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.processinginstruction.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.text.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.undefinednamespacefoundexception.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.unexpectedcharacterexception.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.unexpectedclosingtagexception.h
        ${system.xml_SOURCE_DIR}/include/system.xml/system.xml.unexpectedendoffileexception.h
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
