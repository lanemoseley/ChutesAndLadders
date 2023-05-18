cmake_minimum_required(VERSION 3.22.1)

# Definitions
set(PROJECT_NAME ChutesAndLadders)

# Project Title
project(${PROJECT_NAME} VERSION 1.0)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Boost Dependency
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Copy and Modify about.txt with Version and Build Info
string(TIMESTAMP BUILD_DATE "%Y%m%d")
string(TIMESTAMP BUILD_TIME "%H%M%S")
configure_file(configure/about.txt resources/about.txt)

# Configure Path to Top-Level Project Directory
configure_file(configure/config.h.in ${CMAKE_BINARY_DIR}/config.h)
include_directories(${CMAKE_BINARY_DIR})

# Gather Sources
file(GLOB_RECURSE INC_FILES src/*/*.h)
file(GLOB_RECURSE SRC_FILES src/*/*.cpp)

# Build
set(SOURCE_FILES src/${PROJECT_NAME}.cpp ${INC_FILES} ${SRC_FILES})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

# Post-build, copy the resources directory
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND $(CMAKE_COMMAND) -E copy_directory
        $(CMAKE_SOURCE_DIR)/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

# Boost Unit Tests
add_subdirectory(test)

# CTest
enable_testing()

add_test(NAME VersionTest COMMAND ${PROJECT_NAME} -v)
set_tests_properties(
    VersionTest
    PROPERTIES PASS_REGULAR_EXPRESSION "Version: ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
)
