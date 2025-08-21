// MMOpenGL.cpp: 定义应用程序的入口点。
//

#include "MMOpenGL.h"
#include "Shader/MainShader.h"

void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	std::cout << "窗体大小变化，大小为:" << width << " , " << height << std::endl;
	//更新窗体画布大小
	glViewport(0, 0, width, height);
}

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "键盘消息变化，键为:" << key << " , " << scancode << " , " << action << " , " << mods << std::endl;
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int WindowWidth = 1280;
	int WindowHeight = 720;
	GLFWwindow* GLWindow = glfwCreateWindow(WindowWidth,WindowHeight,"MMOpenGL",NULL,NULL);

	//绑定线程到主线程
	glfwMakeContextCurrent(GLWindow);

	//设置监听窗体大小变化消息
	glfwSetFramebufferSizeCallback(GLWindow, FrameBufferSizeCallBack);
	
	//设置监听键盘消息
	glfwSetKeyCallback(GLWindow,KeyCallBack);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		std::cout << "gladLoadGLLoader  Faild!!!!" << std::endl;
		return 0;
	}

	InitMainShader();

	while (!glfwWindowShouldClose(GLWindow))
	{
		//处理OPenGL消息队列中的内容
		glfwPollEvents();

		UpdateMainShader();

		glfwSwapBuffers(GLWindow);

	}
	

	ShutdownMainShader();
	glfwDestroyWindow(GLWindow);
	glfwTerminate();
	return 0;
}
