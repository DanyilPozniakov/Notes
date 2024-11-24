add_library(TextHandler STATIC
        TextHandler.cpp
        SyntaxHighlighter.cpp
)

target_include_directories(TextHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TextHandler PUBLIC Qt6::Core Qt6::Gui Qt6::QuickControls2
)
