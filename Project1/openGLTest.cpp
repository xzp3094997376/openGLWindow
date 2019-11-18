#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
void Frame_bufferSize_Callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main()
{
	glfwInit();//��ʼ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//�汾ģʽ


	int major, minor, rev;
	glfwGetVersion(&major, &minor, &rev);
	printf("GLFW   %d.%d.%d Init\n",major,minor,rev);

	GLFWwindow* window=glfwCreateWindow(800, 600, "window", NULL, NULL);//��������
	if (window==NULL)
	{
		std::cout << "Failed created" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//���ô���Ϊ��ǰ�߳���������

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//glad����glfw����ָ������
	{
		std::cout << "failed laod process" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);	//���ƴ��ڴ��С
	glfwSetFramebufferSizeCallback(window, Frame_bufferSize_Callback);//���ڱ仯�ص�
	while (!glfwWindowShouldClose(window))//���ڻ����ڼ�һֱ����
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.0f, 0.34f, 0.57f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glfwTerminate();
	return 0;
}
