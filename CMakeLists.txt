cmake_minimum_required(VERSION 3.5)

project(dmstodeg VERSION 0.2.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

configure_file(config.h.in ../include/config.h)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(dmstodeg
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET dmstodeg APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(dmstodeg SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(dmstodeg
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(dmstodeg PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(dmstodeg PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(dmstodeg)
endif()

option(ENABLE_TEST "Turn on to enable tests" OFF)

if (ENABLE_TEST)
		enable_testing()

		set(CATCH2_DIR test)
		add_library(Catch INTERFACE)
		target_include_directories(Catch INTERFACE ${CATCH2_DIR})

		add_subdirectory(test)
endif()

target_include_directories(dmstodeg PUBLIC ../include)

#Get master directory
get_filename_component(MASTER_DIR ${PROJECT_SOURCE_DIR} DIRECTORY)
get_filename_component(MASTER_DIR ${MASTER_DIR} DIRECTORY)

#Execute the script at compile time
add_custom_command(
	TARGET dmstodeg
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND}
		-DHEADER_DIR:PATH="${CMAKE_SOURCE_DIR}"
		-DCACHE_DIR:PATH="${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}"
		-DLANGUAGE:STRING="CXX"
                -P "${PROJECT_SOURCE_DIR}/build_number.cmake"
)
