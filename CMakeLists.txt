cmake_minimum_required(VERSION 3.16)
project(minecraft)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib/utgraphicsutil)
include_directories(src)

add_executable(minecraft
        lib/utgraphicsutil/debuggl.cc
        lib/utgraphicsutil/debuggl.h
        lib/utgraphicsutil/image.h
        lib/utgraphicsutil/jpegio.cc
        lib/utgraphicsutil/jpegio.h
        lib/utgraphicsutil/material.h
        lib/utgraphicsutil/portable_gl.h
        src/config.h
        src/chunk.cpp
        src/chunk.h
        src/gui.cc
        src/gui.h
        src/main.cc
        src/procedure_geometry.cc
        src/procedure_geometry.h
        src/render_pass.cc
        src/render_pass.h
        src/shader_uniform.cc
        src/shader_uniform.h
        src/block.cc
        src/block.h
        src/chunkmanager.cpp
        src/chunkmanager.h
        src/skybox.cpp
        src/skybox.h
        src/perlin.cc
        src/perlin.h
        src/terrain_generator.cc
        src/terrain_generator.h)
