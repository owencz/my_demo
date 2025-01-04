cmake_minimum_required(VERSION 3.30.5)

project(main)

# 配置可执行文件输出路径
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output)

# libpublic.a
# 添加当前目录下的所有 .c 文件到 SRC_PUBLIC 变量
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/lib/elog SRC_PUBLIC)
add_library(public STATIC ${SRC_PUBLIC})
target_include_directories(public PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/elog)

# demo main
add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.c)
target_link_libraries(main public)