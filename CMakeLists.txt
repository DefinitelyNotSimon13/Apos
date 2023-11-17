cmake_minimum_required(VERSION 3.5)

project(Apos-Databasemanager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.6.0\\mingw_64\\lib\\cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql)

set(TS_FILES
    resources/translations/Apos-DatabaseManager_en_GB.ts
    resources/translations/Apos-DatabaseManager_de_DE.ts
)

set(PROJECT_SOURCES
        source/main.cpp
        classes/backendClasses/objecthandler.cpp
        classes/backendClasses/startuphandler.cpp
        classes/databaseClasses/databasehandler.cpp
        classes/databaseClasses/tablehandler.cpp
        classes/frontendClasses/devwindow.cpp
        classes/frontendClasses/launcherwindow.cpp
        classes/frontendClasses/settingswindow.cpp
        classes/frontendClasses/translatablewindow.cpp
        classes/frontendClasses/windowhandler.cpp
        ${TS_FILES}
)

set(PROJECT_HEADERS
    classes/backendClasses/objecthandler.hpp
    classes/backendClasses/startuphandler.hpp
    classes/databaseClasses/databasehandler.hpp
    classes/databaseClasses/tablehandler.hpp
    classes/frontendClasses/devwindow.hpp
    classes/frontendClasses/launcherwindow.hpp
    classes/frontendClasses/settingswindow.hpp
    classes/frontendClasses/translatablewindow.hpp
    classes/frontendClasses/windowhandler.hpp
)

set(PROJECT_UI
    classes/frontendClasses/devwindow.ui
    classes/frontendClasses/launcherwindow.ui
    classes/frontendClasses/settingswindow.ui
)

set(PROJECT_RESOURCES
    resources/colors/AposColorPalette.xml
    resources/colors/colors.txt
    resources/defaultDatabase/userDatabase.db
    resources/images/APOS-ICON.ico
    resources/images/colorTheme.png
    resources/images/icons8-database-50.png
    resources/images/icons8-database-100.png
    resources/other/innoInstallerScript.iss
    resources/other/sqliteCommands.txt
    resources/other/Todo-Versions.txt
    resources/qResources.qrc
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Apos-Databasemanager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_UI}
        ${PROJECT_RESOURCES}


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Apos-Databasemanager APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

qt_add_translations(Apos-Databasemanager TS_FILES ${TS_FILES})

else()
    if(ANDROID)
        add_library(Apos-Databasemanager SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_UI}
            ${PROJECT_RESOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Apos-Databasemanager
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_UI}
            ${PROJECT_RESOURCES}
        )

    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()


target_link_libraries(Apos-Databasemanager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Apos-Databasemanager PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Apos-Databasemanager)
endif()
set_target_properties(Apos-Databasemanager PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Apos-Databasemanager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Apos-Databasemanager)
endif()

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/bin/Qt6Sql${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif ()
