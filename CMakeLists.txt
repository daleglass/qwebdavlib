cmake_minimum_required(VERSION 3.20)


project(Qt-WebDAV VERSION 0.1 LANGUAGES CXX)


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

project(Qt-WebDAV-sample VERSION 0.1 LANGUAGES CXX)
add_executable(Qt-WebDAV-sample ${SAMPLE_SOURCES})

target_include_directories(Qt-WebDAV-sample PRIVATE qwebdavlib)
target_link_libraries(Qt-WebDAV-sample Qt-WebDAV)

