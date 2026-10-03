#################
# Build library #
#################
set(SOURCE_FILES
    gui/qrecentfileaction.cpp
    gui/qcolorbutton.cpp
    gui/page/qpagedialog.cpp
    gui/page/qpagemodel.cpp
    gui/page/qpageview.cpp
    gui/page/qpageview_p.cpp
    gui/page/qpagewidget.cpp
    gui/page/qpagewidgetmodel.cpp
    gui/page/qextenddialog.cpp
    gui/page/klusterseparator.cpp
    gui/dockarea.cpp
    gui/qextendtabwidget.cpp
    gui/qhelpviewer.cpp
    gui/klusterrubberband.cpp
    shared/channelcolors.cpp
    shared/itemcolors.cpp
    shared/zoomwindow.cpp
    shared/utilities.cpp
)

set(RESSOURCE_FILES
    gui/libneurosuite-icons.qrc
    gui/libneurosuite-cursors.qrc
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${RESSOURCE_FILES})
add_library(neurosuite::neurosuite ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
    AUTORCC ON
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE NEUROSUITE_BUILD_NEUROSUITE_LIB QT_USE_QSTRINGBUILDER
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/gui/page
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/gui>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/gui/page>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/shared>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}>
)

################
# Link library #
################
target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Widgets Qt6::PrintSupport)
if(WITH_WEBENGINE)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::WebEngineWidgets)
    target_compile_definitions(${PROJECT_NAME} PRIVATE NEUROSUITE_HAVE_WEBENGINE)
endif()

###################
# Install library #
###################
install(TARGETS ${PROJECT_NAME}
        EXPORT neurosuiteTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set(HEADER_FILES
     libneurosuite_export.h
     gui/qrecentfileaction.h
     gui/qcolorbutton.h
     gui/page/qpagedialog.h
     gui/page/qextenddialog.h
     gui/page/qpagewidget.h
     gui/page/qpagemodel.h
     gui/page/qpageview.h
     gui/page/qpagewidgetmodel.h
     gui/dockarea.h
     gui/qextendtabwidget.h
     gui/qhelpviewer.h
     gui/klusterrubberband.h
     shared/channelcolors.h
     shared/itemcolors.h
     shared/types.h
     shared/array.h
     shared/utilities.h
     shared/zoomwindow.h
)

install(FILES ${HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})
