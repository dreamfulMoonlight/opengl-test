#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

static unsigned int compileShader(const std::string&source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str(); 
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//check
	int success;
	GLchar infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success==GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<(type==GL_VERTEX_SHADER?"vertex:":"fragment:")<< infoLog << std::endl;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader,const std::string &fragmentShader )
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
int main(int argc, char **argv)
{
	
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "My GLFW Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//设置帧率
	glfwSwapInterval(1);
	//初始化glew库,在crreate context之后
	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}

	float position[6] = { 
		-0.5f,-0.5f, //0
		0.0f,0.5f,   //1
		0.5f,-0.5f //2 
	};

	float rect_position[] = {
		-0.5f,-0.5f, //0
		0.5f,-0.5f, //1 
		0.5f,0.5f,   //2

		0.5f,0.5f,   //2
		-0.5f,0.5f, //3
		-0.5f,-0.5f, //0
	};

	float indices_position[] = {
	-0.5f,-0.5f, //0
	0.5f,-0.5f, //1 
	0.5f,0.5f,   //2
	-0.5f,0.5f, //3
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 *2* sizeof(float), indices_position, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	std::string vertexShader = 
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;"
		"\n"
		"void main()\n"
		"{\n"
		" gl_Position= position;\n"
		"}\n";

	std::string fragmentShader = 
		"#version 330 core\n"
		"\n"
		"out vec4 color;\n"
		"\n"
		"uniform vec4 ourColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  color = ourColor;\n"
		"}\n";

	unsigned int shader = CreateShader(vertexShader,fragmentShader);
	glUseProgram(shader);

	int location = glGetUniformLocation(shader, "ourColor");
	//glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);
	/* Loop until the user closes the window */
	float r = 0.0f;
	float increment = 0.05f;

	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* 传统opengl写法

		GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
		*/

		if (r > 1.0f)
			increment = -0.05f;
		else if(r<0.0f)
			increment = 0.05f;

		r += increment;
		glUseProgram(shader);
		glUniform4f(location, r, 0.3f, 0.8f, 1.0f);

		/*no need to bind buffer
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);*/

		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		/*现代opengl写法*/
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		//
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
