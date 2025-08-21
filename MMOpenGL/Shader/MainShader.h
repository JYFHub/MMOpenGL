#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

void InitMainShader();

void InitSharderSource();

void InitVAOVBOEBO();

void SetUniformFloat(const std::string name, float value);

//����Shaderͨ������Shader����
GLuint CreateShader(GLenum type,char* ShaderSource);

GLuint CreateShaderProgram(GLuint VertexShader,GLuint FragmentShader);

void UpdateMainShader();

void ShutdownMainShader();

