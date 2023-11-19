# Set the minimum required version of CMake for this project
cmake_minimum_required(VERSION 3.5)

# Set the project name, version, and languages
project(Apos-Databasemanager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:/Qt/6.6.0/mingw_64/lib/cmake")

# Enable automatic processing of Qt's meta-object compiler (moc)
set(CMAKE_AUTOMOC ON)

# Enable automatic processing of Qt's user interface compiler (uic)
set(CMAKE_AUTOUIC ON)

# Enable automatic processing of Qt's resource compiler (rcc)
set(CMAKE_AUTORCC ON)

# Find the required Qt components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Sql)

# Set the source files for the translation files
set(TS_FILES
        resources/translations/Apos-DatabaseManager_en_GB.ts
        resources/translations/Apos-DatabaseManager_de_DE.ts
)

# Set the source files for the backend classes
set(BACKEND_CLASSES
        classes/backendClasses/objecthandler.cpp
        classes/backendClasses/startuphandler.cpp
        classes/databaseClasses/databasehandler.cpp
        classes/databaseClasses/tablehandler.cpp
)

# Set the source files for the frontend classes
set(FRONTEND_CLASSES
        classes/frontendClasses/devwindow.cpp
        classes/frontendClasses/launcherwindow.cpp
        classes/frontendClasses/settingswindow.cpp
        classes/frontendClasses/translatablewindow.cpp
        classes/frontendClasses/windowhandler.cpp
)

# Set the header files for the backend classes
set(BACKEND_HEADERS
        classes/backendClasses/objecthandler.hpp
        classes/backendClasses/startuphandler.hpp
        classes/databaseClasses/databasehandler.hpp
        classes/databaseClasses/tablehandler.hpp
)

# Set the header files for the frontend classes
set(FRONTEND_HEADERS
        classes/frontendClasses/devwindow.hpp
        classes/frontendClasses/launcherwindow.hpp
        classes/frontendClasses/settingswindow.hpp
        classes/frontendClasses/translatablewindow.hpp
        classes/frontendClasses/windowhandler.hpp
)

# Set the UI files for the frontend classes
set(FRONTEND_UI
        classes/frontendClasses/devwindow.ui
        classes/frontendClasses/launcherwindow.ui
        classes/frontendClasses/settingswindow.ui
)

# Set the resource files for the project
set(PROJECT_RESOURCES
        resources/qResources.qrc
)

# Combine all source files into a single variable
set(PROJECT_FILES
        source/main.cpp
        ${BACKEND_CLASSES}
        ${FRONTEND_CLASSES}
        ${BACKEND_HEADERS}
        ${FRONTEND_HEADERS}
        ${FRONTEND_UI}
        ${PROJECT_RESOURCES}
)

# Add an executable target for the project
qt_add_executable(Apos-Databasemanager
        MANUAL_FINALIZATION
        ${PROJECT_FILES}
)

# Add translations to the project
qt_add_translations(Apos-Databasemanager TS_FILES ${TS_FILES})

# Link the required Qt libraries to the target
target_link_libraries(Apos-Databasemanager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Apos-Databasemanager PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

# Set target properties
set_target_properties(Apos-Databasemanager PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

# Install the target
install(TARGETS Apos-Databasemanager
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the executable target if using Qt 6
if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Apos-Databasemanager)
endif ()

# Add a custom command that runs windeployqt after the project is built
if (WIN32 AND QT_VERSION_MAJOR EQUAL 6)
    add_custom_command(TARGET Apos-Databasemanager POST_BUILD
            COMMAND "C:/Qt/6.6.0/mingw_64/bin/windeployqt.exe"
            "$<TARGET_FILE_DIR:Apos-Databasemanager>/$<TARGET_FILE_NAME:Apos-Databasemanager>"
    )
endif ()