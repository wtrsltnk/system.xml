
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
    XmlNode.cpp
    XmlNodeList.cpp
    XmlProcessingInstruction.cpp
    XmlText.cpp
    XmlWriter.cpp
    XmlWriter.h
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
        ${system.xml_SOURCE_DIR}/include/system.xml/Xml.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlAttribute.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlAttributeCollection.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlCDataSection.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlCharacterData.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlComment.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlDocument.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlDocumentType.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlDuplicateAttributesFoundException.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlElement.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlException.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlLinkedNode.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlName.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlNode.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlNodeList.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlNodeType.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlProcessingInstruction.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlText.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlUndefinedNamespaceFoundException.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlUnexpectedCharacterException.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlUnexpectedClosingTagException.h
        ${system.xml_SOURCE_DIR}/include/system.xml/XmlUnexpectedEndOfFileException.h
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
