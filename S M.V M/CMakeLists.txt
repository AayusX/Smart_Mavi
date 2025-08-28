cmake_minimum_required(VERSION 3.16)
project(SmartMAVIManager VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql Network Charts)

# Enable automatic MOC, UIC, and RCC processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Set include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/models/teacher.cpp
    src/models/student.cpp
    src/models/class.cpp
    src/models/attendance.cpp
    src/models/nepalicalendar.cpp
    src/database/database.cpp
    src/admin/adminpanel.cpp
    src/reports/reports.cpp
    src/widgets/dashboard.cpp
    src/utils/csvhandler.cpp
    src/utils/passwordhash.cpp
    src/dialogs/teacherdialog.cpp
    src/dialogs/studentdialog.cpp
    src/dialogs/classdialog.cpp
    src/dialogs/attendancedialog.cpp
    src/models/enhancedstudent.cpp
    src/communication/communicationmanager.cpp
    src/attendance/advancedattendance.cpp
    src/reports/advancedreports.cpp
    src/settings/settingsmanager.cpp
)

# Header files
set(HEADERS
    include/mainwindow.h
    include/models/teacher.h
    include/models/student.h
    include/models/class.h
    include/models/attendance.h
    include/models/nepalicalendar.h
    include/database/database.h
    include/admin/adminpanel.h
    include/reports/reports.h
    include/widgets/dashboard.h
    include/utils/csvhandler.h
    include/utils/passwordhash.h
    include/dialogs/teacherdialog.h
    include/dialogs/studentdialog.h
    include/dialogs/classdialog.h
    include/dialogs/attendancedialog.h
    include/models/enhancedstudent.h
    include/communication/communicationmanager.h
    include/attendance/advancedattendance.h
    include/reports/advancedreports.h
    include/settings/settingsmanager.h
)

# UI files (if any)
set(UI_FILES
    # Add any .ui files here if needed
)

# Resource files
set(RESOURCES
    resources/resources.qrc
)

# Create executable
add_executable(SmartMAVIManager ${SOURCES} ${HEADERS} ${UI_FILES} ${RESOURCES})

# Link Qt libraries
target_link_libraries(SmartMAVIManager 
    Qt6::Core 
    Qt6::Widgets 
    Qt6::Sql 
    Qt6::Network 
    Qt6::Charts
)

# Set output directory
set_target_properties(SmartMAVIManager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy initial database
file(COPY ${CMAKE_SOURCE_DIR}/data/init_database.sql 
     DESTINATION ${CMAKE_BINARY_DIR}/bin)

# Installation configuration
include(GNUInstallDirs)

# Install executable
install(TARGETS SmartMAVIManager
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install desktop file
install(FILES ${CMAKE_SOURCE_DIR}/packaging/smart-mavi-manager.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)

# Install icon
install(FILES ${CMAKE_SOURCE_DIR}/resources/logo.png
    DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/256x256/apps
    RENAME smart-mavi-manager.png
)

# Install data files
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/
    DESTINATION ${CMAKE_INSTALL_DATADIR}/smart-mavi-manager
    FILES_MATCHING PATTERN "*.sql"
)

# CPack configuration for .deb package
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_NAME "smart-mavi-manager")
set(CPACK_DEBIAN_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Tech07")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Smart MA.VI Manager - School Management System for Shree MA.VI Imilya")
set(CPACK_DEBIAN_PACKAGE_SECTION "Education")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt6core6, libqt6widgets6, libqt6sql6, libqt6network6, libqt6charts6")
set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "sqlite3")

# Windows installer configuration
if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_PACKAGE_NAME "Smart MA.VI Manager")
    set(CPACK_NSIS_DISPLAY_NAME "Smart MA.VI Manager")
    set(CPACK_NSIS_PACKAGE_VERSION ${PROJECT_VERSION})
    set(CPACK_NSIS_CONTACT "Tech07")
    set(CPACK_NSIS_DESCRIPTION "School Management System for Shree MA.VI Imilya")
    set(CPACK_NSIS_MODIFY_PATH ON)
    set(CPACK_NSIS_ENABLE_ICON_EXTRA "${CMAKE_SOURCE_DIR}/resources/logo.png")
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/resources/logo.png")
    set(CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/resources/logo.png")
endif()

include(CPack)
