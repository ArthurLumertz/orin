cmake_minimum_required(VERSION 3.30)
project(Orin_Framework C)

set(CMAKE_C_STANDARD 11)

include_directories(
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/dependencies/include
)

link_directories(
        ${PROJECT_SOURCE_DIR}/dependencies/lib
)

add_executable(Orin_Framework main.c
        src/orin.c
        src/orin.h
        src/orinmath.c
        src/orinmath.h
        dependencies/glad.c
        src/internal/display.h
        src/internal/display.c
        dependencies/include/stb_image.h
        src/internal/texture.h
        src/internal/texture.c
        src/internal/graphics.h
        src/internal/graphics.c
        src/internal/shader.h
        src/internal/shader.c
        src/internal/model.c
        src/internal/model.h
        src/internal/input.h
        src/internal/input.c
)

target_link_libraries(Orin_Framework ${PROJECT_SOURCE_DIR}/dependencies/lib/libglfw.3.dylib)