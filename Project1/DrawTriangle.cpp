#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int main() {
#pragma region ���ڳ�ʼ��
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//���ô�������
	int screen_width=1280;
	int screen_height = 720;
	auto window = glfwCreateWindow(screen_width, screen_height, "�����δ���", nullptr, nullptr);
	if (window==nullptr)
	{
		cout << "��������ʧ��" << endl;
		glfwTerminate();
		return -1;
	}

	//��ʼ��GLAD,����OpenGL����ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "��ʼ������ָ��ʧ��"<<endl;
		return -1;
	}
	//�����ӿ�
	glViewport(0, 0, screen_width, screen_height);
#pragma endregion
#pragma region �����ζ������ݴ���
	const float triangle[] = {
		-0.5f,-0.5f,0.0f,//���£�x,y,z//��һ������(x>-1&&x<<1)
		0.5f,-0.5f,0,//����
		0,0.5f,0//����
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
	
	//���ö�������ָ������:����GPU��δ�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
#pragma endregion
#pragma region ���VAO��VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
#pragma endregion
#pragma region ���������ƬԪ��ɫ��
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
#pragma region ���ɲ��ұ�����ɫ��
	//������ɫ��
	int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source,NULL);
	glCompileShader(vertex_shader);
	//����Ƿ����ɹ�
	int success;
	char info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		cout << info_log << endl;
	}

	//Ƭ����ɫ��
	int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source,NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		cout <<"Ƭ����ɫ�����"<< info_log << endl;
	}

#pragma endregion


}