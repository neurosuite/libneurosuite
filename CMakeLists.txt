# Copyright (C) 2015 Florian Franzen
# Copyright (C) 2025 Joscha Schmiedt
# SPDX-License-Identifier: GPL-3.0-or-later
cmake_minimum_required(VERSION 3.16)
project(neurosuite
    VERSION 3.0.0
    DESCRIPTION "Library for shared functionality of Klusters, NeuroScope and NDManager"
    HOMEPAGE_URL "https://neurosuite.github.io"
    LANGUAGES CXX)

###########
# Options #
###########
option(WITH_WEBENGINE
       "Render the handbook with QtWebEngine (OFF uses QTextBrowser)"
       ON)
option(WITH_TEST
       "Build the scrollarea test binary (not installed)"
       OFF)

##############################
# Configure build environment #
###############################
include(GNUInstallDirs)

# False when an application bundles the library through FetchContent.
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(NEUROSUITE_TOP_LEVEL ON)
else()
    set(NEUROSUITE_TOP_LEVEL OFF)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif()

#####################
# Find dependencies #
#####################
find_package(Qt6 6.4 REQUIRED COMPONENTS Widgets PrintSupport)
if(WITH_WEBENGINE)
    find_package(Qt6 6.4 REQUIRED COMPONENTS WebEngineWidgets)
endif()

########################
# Include subdirectory #
########################
add_subdirectory(src)

if(WITH_TEST)
    add_subdirectory(test)
endif()

##############################
# Create CMake package files #
##############################
set(NEUROSUITE_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/PackageConfig.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${NEUROSUITE_CMAKE_INSTALL_DIR}
)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

if(NEUROSUITE_TOP_LEVEL)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
            DESTINATION ${NEUROSUITE_CMAKE_INSTALL_DIR}
            COMPONENT dev
    )
    install(EXPORT neurosuiteTargets
            NAMESPACE neurosuite::
            DESTINATION ${NEUROSUITE_CMAKE_INSTALL_DIR}
            COMPONENT dev
    )
endif()

# Also allow use from a build tree / FetchContent
export(EXPORT neurosuiteTargets
       NAMESPACE neurosuite::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/neurosuiteTargets.cmake"
)

#######################
# CPack configuration #
#######################
# Skip when built as part of another project (e.g. NeuroScope bundling the library).
if(NEUROSUITE_TOP_LEVEL)
    include(cmake/CPackConfig.cmake)
endif()
