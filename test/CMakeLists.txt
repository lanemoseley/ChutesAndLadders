# Definitions
set(PROJECT_TESTS_NAME ${PROJECT_NAME}_tests)

# Gather Sources
file(GLOB_RECURSE TEST_INC_FILES ${PROJECT_SOURCE_DIR}/test/*.h)
file(GLOB_RECURSE TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

# Assign the include directories
include_directories(${PROJECT_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/src)

# Build unit tests
add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(${PROJECT_TESTS_NAME} ${TEST_SRC_FILES} ${SRC_FILES})
target_link_libraries(${PROJECT_TESTS_NAME} ${Boost_LIBRARIES})

enable_testing()
add_test(${PROJECT_NAME}Test ${PROJECT_TESTS_NAME})
