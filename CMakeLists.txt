cmake_minimum_required(VERSION 3.20)
project(pacgfx C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Werror -ffp-contract=off)

option(PG_SANITIZE "Build with AddressSanitizer + UBSan" OFF)
if(PG_SANITIZE)
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
endif()

add_library(pg_geometry STATIC
    src/geometry/approx.c
    src/geometry/vec2.c
    src/geometry/mat3.c
    src/geometry/angle.c)
target_include_directories(pg_geometry PUBLIC include)
if(UNIX)
    target_link_libraries(pg_geometry PUBLIC m)
endif()

enable_testing()
add_subdirectory(tests)
