cmake_minimum_required(VERSION 3.16)
project(cplus_oop VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE SRC_FILES "src/*.c")
add_library(cplus_oop STATIC ${SRC_FILES})

target_link_libraries(cplus_oop PRIVATE 
    pthread
)

target_compile_options(cplus_oop PRIVATE -mavx2)

target_include_directories(cplus_oop PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(cplus_oop PRIVATE
    -Wall
    -Wextra
    -Werror
    -pedantic
    -Wconversion
    -Wsign-conversion
    -Wshadow
    -Wnull-dereference
    -Wundef
    -Wuninitialized
    -Winit-self
    -Wredundant-decls
    -Wcast-align
    -Wcast-qual
    -Wmissing-declarations
    -Wswitch-default
    -Wdouble-promotion
    -Wformat=2
    -Wwrite-strings
)

option(ENABLE_DEBUG "Enable debug macros and flags" OFF)

if(ENABLE_DEBUG)
    target_compile_definitions(cplus_oop PRIVATE DEBUG=1)
endif()

option(ENABLE_TESTING "Build unit tests" OFF)

if (ENABLE_TESTING)
    file(GLOB TEST_SRC "tests/*.c")
    add_executable(unit_tests ${TEST_SRC})

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang")
        target_compile_options(unit_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
        target_link_options(unit_tests PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_compile_options(unit_tests PRIVATE -fprofile-arcs -ftest-coverage)
        target_link_options(unit_tests PRIVATE -fprofile-arcs -ftest-coverage)
    endif()

    target_compile_definitions(unit_tests PRIVATE UNIT_TESTS=1)
    target_link_libraries(unit_tests PRIVATE criterion cplus_oop)

    enable_testing()
    add_test(NAME unit_tests COMMAND unit_tests)
endif()

add_custom_target(tests_run
    COMMENT "Running unit tests"
    COMMAND ${CMAKE_COMMAND} -DBUILD_TESTS=ON ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target unit_tests
    COMMAND ${CMAKE_BINARY_DIR}/unit_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
