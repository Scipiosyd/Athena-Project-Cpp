cmake_minimum_required(VERSION 3.16)

project(AthenaProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt modules
find_package(Qt6 REQUIRED COMPONENTS Widgets Network WebEngineWidgets)

# Sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    SuburbsWindow.cpp
    SuburbsWindow.h
    medicationwindow.cpp
    medicationwindow.h
    oncallwindow.cpp
    oncallwindow.h
    suburb.h
)

# Add executable
qt_add_executable(AthenaProject
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Link Qt libraries
target_link_libraries(AthenaProject
    PRIVATE
        Qt6::Widgets
        Qt6::Network
        Qt6::WebEngineWidgets
)

# macOS/iOS bundle settings
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AthenaProject)
endif()
set_target_properties(AthenaProject PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AthenaProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable for Qt6
qt_finalize_executable(AthenaProject)
