cmake_minimum_required(VERSION 3.15)
project(MiniEmulator VERSION 1.0 LANGUAGES C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(main
src/main.c
libs/compiler/src/add_var.c
libs/compiler/include/compiler.h
)

add_library(memory
  libs/memory/src/init.c
)
add_library(microops
  libs/microops/src/mov.c
)
add_library(compiler 
  libs/compiler/src/add_var.c
  libs/compiler/src/get_var.c
  libs/compiler/src/get_register.c
  libs/compiler/src/addressing.c
)
target_include_directories(microops PUBLIC libs/microops/include)
target_include_directories(microops PUBLIC libs/globals/include)
target_include_directories(microops PUBLIC libs/compiler/include)

target_include_directories(main PUBLIC libs/globals/include)
target_include_directories(main PUBLIC libs/globals/include)
target_include_directories(main PUBLIC libs/compiler/include)

target_include_directories(memory PUBLIC libs/globals/include)
target_include_directories(memory PUBLIC libs/memory/include)

target_include_directories(compiler PUBLIC libs/globals/include)
target_include_directories(compiler PUBLIC libs/compiler/include)
target_include_directories(compiler PUBLIC libs/memory/include)

target_link_libraries(memory PUBLIC m)

target_link_libraries(main PUBLIC memory compiler microops)