# CMakeList.txt: MMOpenGL 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
cmake_minimum_required (VERSION 3.8)

#包含第三方库目录到项目中 
set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/../Thirdparty/)
set(GLAD_DIR ${THIRDPARTY_DIR}/glad)
set(GLFW_DIR ${THIRDPARTY_DIR}/glfw)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. SRC_LIST)

# 生成链接库
add_library (MMGL STATIC ${SRC_LIST})

target_include_directories(MMGL PUBLIC ${GLAD_DIR}/include/)
target_include_directories(MMGL PUBLIC ${GLFW_DIR}/include/)
target_include_directories(MMGL PUBLIC ${CMAKE_CURRENT_LIST_DIR})

link_directories(${GLFW_DIR}/lib/)


set(PROJECT_BINARY_DIR "${CMAKE_CURRENT_LIST_DIR}/../")

message([[123${ABC}789]])
message("PROJECT_BINARY_DIR:")
message(${PROJECT_BINARY_DIR})
message(STATUS ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/arch")
set(CMAKE_PDB_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

set_target_properties(MMGL PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
 