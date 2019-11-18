#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
void Frame_bufferSize_Callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main()
{
	glfwInit();//初始化
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//版本模式


	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	printf("GLFW   %d.%d.%d Init\n",major,minor,rev);

	GLFWwindow* window=glfwCreateWindow(800, 600, "window", NULL, NULL);//创建窗口
	if (window==NULL)
	{
		std::cout << "Failed created" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//设置窗口为当前线程主上下文

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//glad保存glfw函数指针引用
	{
		std::cout << "failed laod process" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);	//绘制窗口大大小
	glfwSetFramebufferSizeCallback(window, Frame_bufferSize_Callback);//窗口变化回调
	while (!glfwWindowShouldClose(window))//窗口绘制期间一直调用
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glfwTerminate();
	return 0;
}
