cmake_minimum_required(VERSION 3.14)

project(querycasesresult VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()


set(QT_ROOT)

set (QT_STATIC OFF)
if(QT_STATIC)
    set(QT_ROOT "D:/Qt/qtinstall_static_5.15.2")
    if(NOT QT_ROOT IN_LIST CMAKE_PREFIX_PATH)
        list(APPEND CMAKE_PREFIX_PATH ${QT_ROOT})
    endif()
else()
    set(QT_ROOT "D:/Qt5.9.7/5.9.7/msvc2017_64")
    if(NOT QT_ROOT IN_LIST CMAKE_PREFIX_PATH)
        list(APPEND CMAKE_PREFIX_PATH ${QT_ROOT})
    endif()
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

set(BOOST_ROOT "$ENV{BOOST_ROOT}")
set(BOOST_INCLUDEDIR ${BOOST_ROOT})
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/msvc142")
set(Boost_USE_STATIC_LIBS        ON)

find_package(Boost REQUIRED COMPONENTS
    log
)

set(LIBXML_INCLUDE_ROOT "D:/lib_third/libxmlplusplus/all_include/include")
set(LIBXML_LIBRARY_ROOT "D:/lib_third/libxmlplusplus/all_lib/x64_debug/static/lib")

set(LIBXML2_INCLUDE_DIR ${LIBXML_INCLUDE_ROOT}/libxml2)
set(LIBXML2_LIBRARY ${LIBXML_LIBRARY_ROOT}/libxml2.lib)

find_package(LibXml2 REQUIRED)

set(LIBXMLCPLUSCPLUS_INCLUDE_DIRS ${LIBXML_INCLUDE_ROOT}/libxml++-5.0)
set(LIBXMLCPLUSCPLUS_LIBRARIES ${LIBXML_LIBRARY_ROOT}/libxml++.lib)

list(APPEND CMAKE_PREFIX_PATH "D:/lib_third/poco")

find_package(Poco REQUIRED Foundation)

string(TOUPPER ${CMAKE_BUILD_TYPE} build_type)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        logtext.cpp
        logtext.h
        log.h
        resultmodel.cpp
        resultmodel.h
        resulttype.h
        resultstatusitemmodel.h
        resultstatusitemmodel.cpp
        resultmodelitem.cpp
        resultmodelitem.h
        manager.cpp
        manager.h
        querythread.h
        querythread.cpp
        refinecases.h
        prompttext.h
        prompttext.cpp
        configinfo.h
        collector.h
        casemessage.h
        casedetails.h
        iocontextmanager.h
        parsehtml.h
        querymessage.h
        worker.h
        spendtime.h
        emitter.h
        emitter.cpp
)

if(QT_STATIC)
    add_definitions(-DQT_STATIC)
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(querycasesresult
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(querycasesresult SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(querycasesresult
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_compile_features(${PROJECT_NAME} PRIVATE
    cxx_std_17
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${LIBXML2_INCLUDE_DIRS}
    ${LIBXMLCPLUSCPLUS_INCLUDE_DIRS}
)


set(Extra_Static_Lib)

if(QT_STATIC)
    set (Extra_Static_Lib
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Qml
        Qt${QT_VERSION_MAJOR}::Gui
        ${QT_ROOT}/qml/QtQuick.2/qtquick2plugind.lib
        ${QT_ROOT}/qml/QtQuick/Controls/qtquickcontrolsplugind.lib
        ${QT_ROOT}/qml/QtQuick/Controls.2/qtquickcontrols2plugind.lib
        ${QT_ROOT}/qml/QtQuick/Layouts/qquicklayoutsplugind.lib
        ${QT_ROOT}/qml/QtQuick/Window.2/windowplugind.lib
        ${QT_ROOT}/qml/QtQuick/Templates.2/qtquicktemplates2plugind.lib
        ${QT_ROOT}/qml/QtQml/qmlplugind.lib
        ${QT_ROOT}/lib/Qt5QmlWorkerScriptd.lib
        ${QT_ROOT}/lib/Qt5QuickControls2d.lib
        ${QT_ROOT}/lib/Qt5QuickTemplates2d.lib
    )
endif()


target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    ${Boost_LIBRARIES}
    LibXml2::LibXml2
    ${LIBXMLCPLUSCPLUS_LIBRARIES}
    Poco::Foundation
    ${Extra_Static_Lib}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(querycasesresult)
    qt_finalize_executable(querycasesresult)
endif()
