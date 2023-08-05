cmake_minimum_required(VERSION 3.20)


project(Qt-WebDAV VERSION 0.1 LANGUAGES CXX)

option(BUILD_SAMPLES "Build the sample programs" ON)
option(DEBUG "Build with debug output" OFF)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CURRENT_SOURCE_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_DEBUG_POSTFIX dbg)

set(USE_QT_VERSION 5)

include_directories( ${PROJECT_SOURCE_DIR} )


message(STATUS "Building for Qt ${USE_QT_VERSION}")
message(STATUS "Build type (-DCMAKE_BUILD_TYPE    : ${CMAKE_BUILD_TYPE}")
message(STATUS "Building samples (-DBUILD_SAMPLES): ${BUILD_SAMPLES}")
message(STATUS "Debug ouput (-DDEBUG)             : ${DEBUG}")

find_package(Qt${USE_QT_VERSION} REQUIRED COMPONENTS Core Network Xml)

set(LIBRARY_SOURCES
    qwebdavlib/qnaturalsort.cpp
    qwebdavlib/qwebdav.cpp
    qwebdavlib/qwebdavdirparser.cpp
    qwebdavlib/qwebdavitem.cpp
    )

set(SAMPLE_SOURCES
    qwebdavlibExample/main.cpp
    qwebdavlibExample/qexample.cpp
)


add_library(Qt-WebDAV SHARED ${LIBRARY_SOURCES})
target_link_libraries(Qt-WebDAV Qt${USE_QT_VERSION}::Core Qt${USE_QT_VERSION}::Network Qt${USE_QT_VERSION}::Xml)

if (MSVC)
    target_compile_options(Qt-WebDAV PUBLIC /W4 /WX)
else()
    target_compile_options(Qt-WebDAV PUBLIC -Wall -Wextra -Werror)
endif()

if (DEBUG)
    target_compile_definitions(Qt-WebDAV PUBLIC DEBUG_WEBDAV)
endif()


if(BUILD_SAMPLES)
    project(Qt-WebDAV-sample VERSION 0.1 LANGUAGES CXX)
    add_executable(Qt-WebDAV-sample ${SAMPLE_SOURCES})

    target_include_directories(Qt-WebDAV-sample PRIVATE qwebdavlib)
    target_link_libraries(Qt-WebDAV-sample Qt-WebDAV)

    if (MSVC)
        target_compile_options(Qt-WebDAV-sample PUBLIC /W4 /WX)
    else()
        target_compile_options(Qt-WebDAV-sample PUBLIC -Wall -Wextra -Werror)
    endif()
endif()

