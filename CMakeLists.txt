cmake_minimum_required(VERSION 3.20)


project(Qt-WebDAV VERSION 0.1 LANGUAGES CXX)

option(BUILD_SAMPLES "Build the sample programs" ON)
option(DEBUG "Build with debug output" OFF)
option(EXTENDED_PROPERTIES "Support extended item properties" ON)

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
message(STATUS "Build type (-DCMAKE_BUILD_TYPE             : ${CMAKE_BUILD_TYPE}")
message(STATUS "Building samples (-DBUILD_SAMPLES)         : ${BUILD_SAMPLES}")
message(STATUS "Debug ouput (-DDEBUG)                      : ${DEBUG}")
message(STATUS "Extended properties (-DEXTENDED_PROPERTIES): ${EXTENDED_PROPERTIES}")

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
set_target_properties(Qt-WebDAV PROPERTIES PUBLIC_HEADER "qwebdavlib/qnaturalsort.h;qwebdavlib/qwebdav.h;qwebdavlib/qwebdavdirparser.h;qwebdavlib/qwebdavitem.h;qwebdavlib/qwebdav_global.h")


if (MSVC)
    target_compile_options(Qt-WebDAV PUBLIC /W4 /WX)
else()
    target_compile_options(Qt-WebDAV PUBLIC -Wall -Wextra -Werror)
endif()

if (DEBUG)
    target_compile_definitions(Qt-WebDAV PUBLIC DEBUG_WEBDAV)
endif()

if(EXTENDED_PROPERTIES)
    target_compile_definitions(Qt-WebDAV PUBLIC QWEBDAVITEM_EXTENDED_PROPERTIES)
endif()
include(GNUInstallDirs)

install(TARGETS Qt-WebDAV LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}" PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/qwebdavlib" )
install(FILES LICENSE README CHANGES DESTINATION "${CMAKE_INSTALL_DOCDIR}")

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

    install(TARGETS Qt-WebDAV-sample RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
endif()

