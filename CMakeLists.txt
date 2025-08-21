# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

project ("MMOpenGL"
VERSION 1.0.0.0
)

# 包含子项目。
add_subdirectory ("MMOpenGL")
add_subdirectory ("MMGL")

# 打印CMake 编译过程
set(CMAKE_VERBOSE_MAKEFILEON ON)

# 设置C++标准 为C++11
set(CMAKE_CXX_STANDARD 11)

# 打印工程名称 版本 源码路径等
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "Source dir: ${PROJECT_SOURCE_DIR}")
message(STATUS "Binary dir: ${PROJECT_BINARY_DIR}")
message(STATUS "Generator: ${CMAKE_GENERATOR}")