cmake_minimum_required(VERSION 3.16)

project(Notes VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/msvc2022_64")

find_package(Qt6 6.8 COMPONENTS Core Quick qml QuickControls2 Gui REQUIRED)

set(LLVM_DIR "C:/Program Files/LLVM")
include_directories("${LLVM_DIR}/include")
link_directories("${LLVM_DIR}/lib")

add_subdirectory(src/TextHandler TextHandler)

qt_add_executable(appNotes main.cpp)


qt_add_resources(appNotes
    PREFIX /
    FILES keywords.json
    jsonResurces.qrc
)
qt_add_qml_module(appNotes
    URI Notes
    VERSION 1.0
    QML_FILES
        qml/main.qml
        qml/NoteEditor.qml
        qml/TopMenuBar.qml
        qml/SettingsWindow.qml
        qml/LeftBar.qml
    SOURCES
        src/CoreApp/AppCore.cpp src/CoreApp/AppCore.h
        src/Parsers/JsonParser.h src/Parsers/JsonParser.cpp
        src/FileSystem/FileHandler.h src/FileSystem/FileHandler.cpp
        src/CoreApp/Models/CategoryModel.cpp src/CoreApp/Models/CategoryModel.h
        src/CoreApp/Models/CategoryItem.cpp src/CoreApp/Models/CategoryItem.h
        src/CoreApp/Models/File.cpp src/CoreApp/Models/File.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appNotes PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appNotes
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE
)



target_link_libraries(appNotes
    PRIVATE Qt6::Quick
            Qt6::Qml
            Qt6::Core
            Qt6::Gui
            Qt6::QuickControls2
            TextHandler
            libclang
  )

if (WIN32)

    find_program(WINDEPLOYQT_EXECUTABLE windeployqt
            PATHS ${Qt6_DIR}/6.8.0/msvc2022_64/bin
            ENV PATH
    )

    if (WINDEPLOYQT_EXECUTABLE)
        message(STATUS "windeployqt find: ${WINDEPLOYQT_EXECUTABLE}")
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(WINDEPLOYQT_FLAGS "--debug")
        else()
            set(WINDEPLOYQT_FLAGS "--release")
        endif()

        add_custom_command(TARGET appNotes POST_BUILD
                COMMAND ${WINDEPLOYQT_EXECUTABLE} ${WINDEPLOYQT_FLAGS}  "$<TARGET_FILE:appNotes>"
                COMMENT "windeployqt..."
        )
    else()
        message(FATAL_ERROR "windeployqt is not found")
    endif()

endif()

include(GNUInstallDirs)
install(TARGETS appNotes
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
