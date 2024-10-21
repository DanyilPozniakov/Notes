cmake_minimum_required(VERSION 3.16)

project(Notes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "D:/Qt/6.7.3/msvc2022_64")
find_package(Qt6 6.2 COMPONENTS Quick Qml REQUIRED)

qt_add_executable(appNotes
    main.cpp
)

qt_add_resources(appNotes jsonResurces.qrc )

qt_add_resources(appNotes
    PREFIX /
    FILES keywords.json
)
qt_add_qml_module(appNotes
    URI Notes
    VERSION 1.0
    QML_FILES main.qml
    SOURCES src/texthandler.h src/texthandler.cpp
    SOURCES src/texthandler.cpp src/texthandler.h
    SOURCES src/texthandler.cpp src/texthandler.h
    SOURCES src/parsers/JsonParser.hpp src/parsers/JsonParser.cpp SOURCES
    QML_FILES NoteEditor.qml

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appNotes PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appNotes
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appNotes
    PRIVATE Qt6::Quick
            Qt6::Qml)

include(GNUInstallDirs)
install(TARGETS appNotes
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
