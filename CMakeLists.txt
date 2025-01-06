cmake_minimum_required(VERSION 3.28.3)

project(main)

# 配置可执行文件输出路径
set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/output)

# 配置编译选项
add_compile_options(-Wall -Os)

# libpublic.a
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/lib)

# test 下的子项目
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
