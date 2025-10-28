cmake_minimum_required(VERSION 3.16)
project(AayushTech07Dashboard VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS 
    Widgets
    Charts
    PrintSupport
    REQUIRED
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/login.cpp
    src/dashboard.cpp
    src/student_dialog.cpp
)

# Header files
set(HEADERS
    include/common.h
    include/login.h
    include/dashboard.h
    include/student_dialog.h
)

# Asset files to include
configure_file(${CMAKE_SOURCE_DIR}/assets/style.qss ${CMAKE_BINARY_DIR}/assets/style.qss COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/assets/students.json ${CMAKE_BINARY_DIR}/assets/students.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/assets/users.json ${CMAKE_BINARY_DIR}/assets/users.json COPYONLY)

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Charts
    Qt6::PrintSupport
)

# Install rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Copy assets to build directory
file(COPY ${CMAKE_SOURCE_DIR}/assets/style.qss
     DESTINATION ${CMAKE_BINARY_DIR}/assets)
file(COPY ${CMAKE_SOURCE_DIR}/assets/students.json
     DESTINATION ${CMAKE_BINARY_DIR}/assets)
file(COPY ${CMAKE_SOURCE_DIR}/assets/users.json
     DESTINATION ${CMAKE_BINARY_DIR}/assets)