cmake_minimum_required(VERSION 3.5)

project(dmstodeg VERSION 0.7.0)

CMAKE_POLICY(SET CMP0020 NEW)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resources/img/dmstodeg_icon.o")

#set(CMAKE_PREFIX_PATH "/usr/lib64/cmake/Qt5/")
#set(CMAKE_PREFIX_PATH "/usr/Qt/5.15.3/x86_64-w64-mingw32/")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

configure_file(config.h.in ../include/config.h)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/aboutwindow.h
        src/aboutwindow.cpp
        src/aboutwindow.ui
)


IF(MINGW)
        add_executable(dmstodeg WIN32 ${PROJECT_SOURCES} ${APP_ICON_RESOURCE_WINDOWS})
ELSE()
        add_executable(dmstodeg WIN32 ${PROJECT_SOURCES})
ENDIF()

set_property(TARGET dmstodeg PROPERTY WIN32_EXECUTABLE true)
set_target_properties(dmstodeg PROPERTIES
    WIN32_EXECUTABLE TRUE
)
IF(MINGW)
        set_target_properties(dmstodeg PROPERTIES LINK_FLAGS "-mwindows")
ENDIF()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

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
