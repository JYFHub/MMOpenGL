# CMakeList.txt: MMOpenGL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

#包含第三方库目录到项目中 
set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/../Thirdparty/)
set(GLAD_DIR ${THIRDPARTY_DIR}/glad)
set(GLFW_DIR ${THIRDPARTY_DIR}/glfw)
#add_subdirectory(${THIRDPARTY_DIR}/Thirdparty thirdparty_binary_dir)

include_directories(${GLAD_DIR}/include/)
include_directories(${GLFW_DIR}/include/)
include_directories(${CMAKE_CURRENT_LIST_DIR})

link_directories(${GLFW_DIR}/lib/)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. SRC_LIST)

# 将源代码添加到此项目的可执行文件。
add_executable (MMOpenGL
	${SRC_LIST}
	${GLAD_DIR}/src/glad.c
	${CMAKE_CURRENT_LIST_DIR}/Shader/MainShader.cpp
	)

# TODO: 如有需要，请添加测试并安装目标。
target_link_libraries(MMOpenGL glfw3)