// MMOpenGL.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#pragma once
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>



void  FrameBufferSizeCallBack(GLFWwindow* window, int width, int height);

void  KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
