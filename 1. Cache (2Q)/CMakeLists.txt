#########################################################################

# CMAKE MINIMAL VERSION
cmake_minimum_required (VERSION 3.11)

# PROJECT PROPERTIES
project ("Cache2Q" LANGUAGES CXX)

#########################################################################

# EXECUTABLE FILE PROPERTIES
set(CACHE_NAME          "cache")
set(CACHE_NAME_LOGS_ON  "cache_log")
set(CACHE_GEN_TEST      "cache_test")

set(HEADERS
    include/page.hpp
    include/cache_mem.hpp
    include/2q_cache.hpp
)

set(CACHE_SOURCES
    src/main.cpp
)

set(TEST_SOURCES
    tests/main.cpp
)

# EXECUTABLE FILE
add_executable(${CACHE_NAME}         ${CACHE_SOURCES})
add_executable(${CACHE_NAME_LOGS_ON} ${CACHE_SOURCES})
add_executable(${CACHE_GEN_TEST}     ${TEST_SOURCES})

target_include_directories(${CACHE_NAME}         PRIVATE include src)
target_include_directories(${CACHE_NAME_LOGS_ON} PRIVATE include src)
target_include_directories(${CACHE_GEN_TEST}     PRIVATE include tests)

target_compile_definitions(${CACHE_NAME_LOGS_ON} PRIVATE LOG_ON)


#########################################################################

# ASSEMBLY OPTIONS
set_target_properties(${CACHE_NAME} PROPERTIES
    CXX_STANDARD          20
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(${CACHE_NAME_LOGS_ON} PROPERTIES
    CXX_STANDARD          20
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(${CACHE_GEN_TEST} PROPERTIES
    CXX_STANDARD          20
    CXX_STANDARD_REQUIRED ON
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

#########################################################################