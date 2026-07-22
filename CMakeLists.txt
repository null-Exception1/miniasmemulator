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
  libs/microops/src/alu/sub.c
  libs/microops/src/alu/add.c
  libs/microops/src/alu/mul.c
  libs/microops/src/alu/div.c
  libs/microops/src/logic/xor.c
  libs/microops/src/logic/and.c
  libs/microops/src/logic/or.c
  libs/microops/src/logic/not.c
  libs/microops/src/mov.c
  libs/microops/src/flow/cmp.c
)
add_library(compiler 
  libs/compiler/src/add_var.c
  libs/compiler/src/get_var.c
  libs/compiler/src/get_register.c
  libs/compiler/src/addressing.c
  libs/compiler/src/global_parser.c
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
target_include_directories(compiler PUBLIC libs/microop/include)
target_link_libraries(memory PUBLIC m)
target_link_libraries(microops PUBLIC compiler)
target_link_libraries(main PUBLIC memory compiler microops)