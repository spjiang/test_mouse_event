cmake_minimum_required(VERSION 3.28)
project(test_mouse_event)
project(test_mouse_event VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt6核心模块
find_package(Qt6 6.5 REQUIRED
        COMPONENTS
        Network
        QuickWidgets
        Gui
        Widgets
        Core
)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        MouseSimulator.h
        MouseSimulator.cpp
)

# 添加可执行文件
qt_add_executable(test_mouse_event
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
)

# 链接Qt库
target_link_libraries(test_mouse_event PRIVATE
        Qt6::Widgets
)

add_custom_command(TARGET test_mouse_event POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rename $<TARGET_FILE:test_mouse_event> ${CMAKE_SOURCE_DIR}/installer/test_mouse_event.exe
        COMMENT "Copying my_executable to installer directory"
)

include_directories("${PROJECT_SOURCE_DIR}/")

set_target_properties(test_mouse_event PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)
include(GNUInstallDirs)

#install(TARGETS powerpoint DESTINATION ${CMAKE_SOURCE_DIR}/installer)
qt_finalize_executable(test_mouse_event)
