# ==============================================================================
# 
#   Based on the vscode-cpp-template
#   Created by:
#     - Adam Jeliński (charodziej)
#
#   https://github.com/charodziej/vscode-cpp-template
#
# ==============================================================================

cmake_minimum_required(VERSION 3.11.0)
project(my_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include and configure GoogleTest
include(FetchContent)
FetchContent_Declare( 
    googletest
    GIT_REPOSITORY      https://github.com/google/googletest.git
    GIT_TAG main
)
FetchContent_MakeAvailable(googletest)
enable_testing()

# macro to find subdirectories
# https://stackoverflow.com/a/7788165
MACRO(SUBDIRLIST result curdir)
    FILE(GLOB_RECURSE children LIST_DIRECTORIES true CONFIGURE_DEPENDS ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

# find subdirectories in src that contain code for classes
SUBDIRLIST(SOURCE_DIRECTORIES src)

# in each subdirectory, find cpp files and add them to the source list
set(SOURCES "")
set(TEST_SOURCES "")
FOREACH(subdir ${SOURCE_DIRECTORIES})
    FILE(GLOB sources CONFIGURE_DEPENDS ${subdir}/*.cpp)
    FILE(GLOB test_sources CONFIGURE_DEPENDS ${subdir}/test*.cpp)

    LIST(APPEND SOURCES ${sources})
    IF(test_sources)
        LIST(REMOVE_ITEM SOURCES ${test_sources})
    ENDIF()

    LIST(APPEND TEST_SOURCES ${test_sources})
ENDFOREACH()

# include the source directories
include_directories(src)

# create a build target for the main project file
add_executable(main src/main.cpp ${SOURCES})

# create a build target for the testing file
add_executable(tests src/tests.cpp ${TEST_SOURCES} ${SOURCES})
target_link_libraries(tests PUBLIC gtest_main)

# initialize GoogleTest
include(GoogleTest)
gtest_discover_tests(tests)
