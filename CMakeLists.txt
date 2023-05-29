cmake_minimum_required (VERSION 3.12)
project (isonata C CXX)
enable_testing ()
set (CMAKE_CXX_STANDARD 14)

option (ENABLE_SONATA "Enable Sonata implementation" OFF)
option (ENABLE_YOKAN "Enable Yokan implementation" OFF)
option (ENABLE_TESTS "Enable tests" OFF)

# add our cmake module directory to the path
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
     "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# link shared lib with full rpath
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#
# library version set here (e.g. for shared libs).
#
set (ISONATA_VERSION_MAJOR 0)
set (ISONATA_VERSION_MINOR 2)
set (ISONATA_VERSION_PATCH 0)
set (isonata-vers "${ISONATA_VERSION_MAJOR}.${ISONATA_VERSION_MINOR}")
set (ISONATA_VERSION "${isonata-vers}.${ISONATA_VERSION_PATCH}")

# load package helper for generating cmake CONFIG packages
include (CMakePackageConfigHelpers)

# where to install files for "find_package"
set (isonata-pkg "share/cmake/isonata")

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
  set (SERVER_PC_REQ sonata-server)
  set (ADMIN_PC_REQ sonata-admin)
  set (CLIENT_PC_REQ sonata-client)
endif (${ENABLE_SONATA})

if (${ENABLE_YOKAN})
  find_package (yokan REQUIRED)
  set (SERVER_DEPS ${SERVER_DEPS} yokan-server)
  set (ADMIN_DEPS  ${ADMIN_DEPS}  yokan-admin yokan-client)
  set (CLIENT_DEPS ${CLIENT_DEPS} yokan-client)
  set (SERVER_PC_REQ yokan-server)
  set (ADMIN_PC_REQ yokan-admin yokan-client)
  set (CLIENT_PC_REQ yokan-client)
endif (${ENABLE_YOKAN})

configure_file (src/Config.hpp.in Config.hpp)

add_library (isonata-server ${CMAKE_CURRENT_SOURCE_DIR}/src/Provider.cpp)
target_link_libraries (isonata-server PUBLIC thallium PRIVATE ${SERVER_DEPS})
target_include_directories (isonata-server PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories (isonata-server BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_include_directories (isonata-server BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
set_target_properties (isonata-server PROPERTIES VERSION ${ISONATA_VERSION} SOVERSION ${ISONATA_VERSION_MAJOR})

add_library (isonata-client ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp)
target_link_libraries (isonata-client PUBLIC thallium nlohmann_json PRIVATE ${CLIENT_DEPS})
target_include_directories (isonata-client PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories (isonata-client BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_include_directories (isonata-client BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
set_target_properties (isonata-client PROPERTIES VERSION ${ISONATA_VERSION} SOVERSION ${ISONATA_VERSION_MAJOR})

add_library (isonata-admin ${CMAKE_CURRENT_SOURCE_DIR}/src/Admin.cpp)
target_link_libraries (isonata-admin PUBLIC thallium nlohmann_json PRIVATE ${ADMIN_DEPS})
target_include_directories (isonata-admin PUBLIC $<INSTALL_INTERFACE:include>)
target_include_directories (isonata-admin BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_include_directories (isonata-admin BEFORE PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)
set_target_properties (isonata-client PROPERTIES VERSION ${ISONATA_VERSION} SOVERSION ${ISONATA_VERSION_MAJOR})

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

#
# installation stuff (packaging and install commands)
#
write_basic_package_version_file (
    "isonata-config-version.cmake"
    VERSION ${ISONATA_VERSION}
    COMPATIBILITY AnyNewerVersion)

# generate our config file for find_package()
configure_file (src/isonata-config.cmake.in isonata-config.cmake @ONLY)

set (DEST_DIR ${CMAKE_INSTALL_PREFIX})
configure_file (src/isonata-client.pc.in isonata-client.pc @ONLY)
configure_file (src/isonata-server.pc.in isonata-server.pc @ONLY)
configure_file (src/isonata-admin.pc.in isonata-admin.pc @ONLY)

#
# "make install" rules
#
install (TARGETS isonata-client isonata-server isonata-admin EXPORT isonata-targets
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib)
install (EXPORT isonata-targets
         DESTINATION ${isonata-pkg}
         FILE "isonata-targets.cmake")
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/isonata-config.cmake
               ${CMAKE_CURRENT_BINARY_DIR}/isonata-config-version.cmake
         DESTINATION ${isonata-pkg} )
install (DIRECTORY include/isonata
         DESTINATION include
         FILES_MATCHING PATTERN "*.hpp")
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/isonata-client.pc"
         DESTINATION "lib/pkgconfig/")
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/isonata-admin.pc"
         DESTINATION "lib/pkgconfig/")
install (FILES "${CMAKE_CURRENT_BINARY_DIR}/isonata-server.pc"
         DESTINATION "lib/pkgconfig/")
