cmake_minimum_required (VERSION 3.12)
project (isonata C CXX)
enable_testing ()
set (CMAKE_CXX_STANDARD 14)

option (ENABLE_SONATA "Enable Sonata implementation" OFF)
option (ENABLE_TESTS  "Enable tests" OFF)

# add our cmake module directory to the path
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
     "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# link shared lib with full rpath
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# setup cache variables for ccmake
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release
         CACHE STRING "Choose the type of build." FORCE)
    set_property (CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
                  "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif ()
set (CMAKE_PREFIX_PATH "" CACHE STRING "External dependencies path")
set (BUILD_SHARED_LIBS "ON" CACHE BOOL "Build a shared library")

find_package (thallium REQUIRED)
find_package (nlohmann_json REQUIRED)
if (${ENABLE_SONATA})
  find_package (sonata REQUIRED)
  set (SERVER_DEPS ${SERVER_DEPS} sonata-server)
  set (ADMIN_DEPS  ${ADMIN_DEPS}  sonata-admin)
  set (CLIENT_DEPS ${CLIENT_DEPS} sonata-client)
endif (${ENABLE_SONATA})

configure_file (src/Config.hpp.in Config.hpp)

add_library (isonata-server ${CMAKE_CURRENT_SOURCE_DIR}/src/Provider.cpp)
target_link_libraries (isonata-server PUBLIC thallium PRIVATE ${SERVER_DEPS})
target_include_directories (isonata-server PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories (isonata-server BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_include_directories (isonata-server BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

add_library (isonata-client ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp)
target_link_libraries (isonata-client PUBLIC thallium nlohmann_json PRIVATE ${CLIENT_DEPS})
target_include_directories (isonata-client PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories (isonata-client BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_include_directories (isonata-client BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

add_library (isonata-admin ${CMAKE_CURRENT_SOURCE_DIR}/src/Admin.cpp)
target_link_libraries (isonata-admin PUBLIC thallium nlohmann_json PRIVATE ${ADMIN_DEPS})
target_include_directories (isonata-admin PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories (isonata-admin BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_include_directories (isonata-admin BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

if (${ENABLE_TESTS})
    enable_testing ()
    find_package (Catch2 QUIET)
    if (NOT Catch2_FOUND)
        include (FetchContent)
        FetchContent_Declare (
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v3.0.1
        )
        FetchContent_MakeAvailable (Catch2)
    endif ()
    add_subdirectory (tests)
endif (${ENABLE_TESTS})
