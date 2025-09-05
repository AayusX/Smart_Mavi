cmake_minimum_required(VERSION 3.16)

project(SmartMaviManager VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets PrintSupport)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/surveydialog.cpp
    src/teacher.cpp
    src/subject.cpp
    src/classinfo.cpp
    src/timeslot.cpp
    src/schedule.cpp
    src/schedulegenerator.cpp
    src/scheduleview.cpp
)

# Header files
set(HEADERS
    include/mainwindow.h
    include/surveydialog.h
    include/teacher.h
    include/subject.h
    include/classinfo.h
    include/timeslot.h
    include/schedule.h
    include/schedulegenerator.h
    include/scheduleview.h
)

# Create executable
add_executable(SmartMaviManager ${SOURCES} ${HEADERS})

# Link Qt5 libraries
target_link_libraries(SmartMaviManager Qt5::Core Qt5::Widgets Qt5::PrintSupport)

# Copy resources
configure_file(${CMAKE_SOURCE_DIR}/resources/logo.png ${CMAKE_BINARY_DIR}/logo.png COPYONLY)

# Set executable properties for Windows
if(WIN32)
    set_target_properties(SmartMaviManager PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
endif()

# Enable MOC for Qt meta-object compilation
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Make sure MOC finds all headers
set(CMAKE_INCLUDE_CURRENT_DIR ON)
