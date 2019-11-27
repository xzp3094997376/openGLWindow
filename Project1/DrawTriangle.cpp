#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int main() {
#pragma region 窗口初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//设置窗口属性
	int screen_width=1280;
	int screen_height = 720;
	auto window = glfwCreateWindow(screen_width, screen_height, "三角形窗口", nullptr, nullptr);
	if (window==nullptr)
	{
		cout << "创建窗口失败" << endl;
		glfwTerminate();
		return -1;
	}

	//初始化GLAD,管理OpenGL函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "初始化函数指针失败"<<endl;
		return -1;
	}
	//创建视口
	glViewport(0, 0, screen_width, screen_height);
#pragma endregion
#pragma region 三角形顶点数据处理
	const float triangle[] = {
		-0.5f,-0.5f,0.0f,//左下，x,y,z//归一化坐标(x>-1&&x<<1)
		0.5f,-0.5f,0,//右下
		0,0.5f,0//正上
	};
	//VAO
	GLuint vertext_array_object;
	glGenVertexArrays(1, &vertext_array_object);
	glBindVertexArray(vertext_array_object);
	//VBO
	GLuint vertex_buffer_object;//VBO
	glGenBuffers(1, &vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	
	//设置顶点数据指针属性:告诉GPU如何处理数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
#pragma endregion
#pragma region 解绑VAO和VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#pragma endregion
#pragma region 创建顶点和片元着色器
	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout(location=0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"gl_Postion=vec4(aPos,1.0);\n"
		"}\n\0";
	const char* fragment_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
		"}\n\0";
#pragma endregion
#pragma region 生成并且编译着色器
	//顶点着色器
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source,NULL);
	glCompileShader(vertex_shader);
	//检查是否编译成功
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		cout << info_log << endl;
	}

	//片段着色器
	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source,NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		cout <<"片段着色器检查"<< info_log << endl;
	}

#pragma endregion


}