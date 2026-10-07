# CPack settings for libneurosuite (DEB on Linux, ZIP elsewhere).
set(CPACK_PACKAGE_NAME "libneurosuite")
set(CPACK_PACKAGE_VENDOR "Neurosuite")
set(CPACK_PACKAGE_CONTACT "Florian Franzen <FlorianFranzen@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set(CPACK_SOURCE_IGNORE_FILES "/\\\\.git/;/build.*/;/result")

if(UNIX AND NOT APPLE)
    # Two packages, as in Debian: libneurosuite3 (shared library) and
    # libneurosuite-dev (headers, CMake package, link). The applications'
    # .debs depend on libneurosuite3 through the generated shlibs file.
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEB_COMPONENT_INSTALL ON)
    set(CPACK_COMPONENTS_ALL runtime dev)
    set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
    set(CPACK_DEBIAN_PACKAGE_SECTION "libs")

    set(CPACK_DEBIAN_RUNTIME_PACKAGE_NAME "libneurosuite${PROJECT_VERSION_MAJOR}")
    set(CPACK_DEBIAN_RUNTIME_PACKAGE_SHLIBDEPS ON)
    set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)
    set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS_POLICY ">=")
    set(CPACK_DEBIAN_RUNTIME_PACKAGE_SUGGESTS "neuroscope, klusters, ndmanager")

    set(CPACK_DEBIAN_DEV_PACKAGE_NAME "libneurosuite-dev")
    set(CPACK_DEBIAN_DEV_PACKAGE_SECTION "libdevel")
    set(CPACK_DEBIAN_DEV_PACKAGE_DEPENDS "qt6-base-dev")
    set(CPACK_COMPONENT_DEV_DEPENDS runtime)
    set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
else()
    set(CPACK_GENERATOR "ZIP")
endif()

include(CPack)
