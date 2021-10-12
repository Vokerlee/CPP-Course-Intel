#########################################################################

# CMAKE MINIMAL VERSION
cmake_minimum_required (VERSION 3.8)

# PROJECT PROPERTIES
project ("Triangles" LANGUAGES CXX)

#########################################################################

# EXECUTABLE FILE PROPERTIES
set(FILE_NAME       "triangle")
set(TESTS_FILE_NAME "tr_tests")

set(TRIANGLE_HEADERS
        include/vector.hpp
        include/point.hpp
        include/line.hpp
        include/plane.hpp
        include/triangle.hpp
)

set(TRIANGLE_SOURCES
        src/main.cpp
        src/vector.cpp
        src/point.cpp
        src/line.cpp
        src/plane.cpp
        src/triangle.cpp
)

set(TESTS_SOURCES
        src/tests.cpp  
        src/vector.cpp
        src/point.cpp
        src/line.cpp
        src/plane.cpp
        src/triangle.cpp      
)

# EXECUTABLE FILE
add_executable(${FILE_NAME}       ${TRIANGLE_SOURCES})
add_executable(${TESTS_FILE_NAME} ${TESTS_SOURCES})

target_include_directories(${FILE_NAME}       PRIVATE include)
target_include_directories(${TESTS_FILE_NAME} PRIVATE include)

target_link_libraries(${TESTS_FILE_NAME} gtest)

#########################################################################

# ASSEMBLY OPTIONS
set_target_properties(${FILE_NAME} PROPERTIES
    CXX_STANDARD          14
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