#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include"render.h"

#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"

static unsigned int compileShader(const std::string&source, unsigned int type)
{
	unsigned int id = glCreateShader(type);  
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);	
	glCompileShader(id);

	return id;

}


static unsigned int CreateShader(const std::string& vertexShader, const std::string &fragmentShader)
{
	unsigned int program = glCreateProgram(); 
	unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glUseProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


int main(int argc, char **argv)
{
	const char *glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);  

	if (!glfwInit())
		return -1;
	GLFWwindow *window = glfwCreateWindow(1280, 720, "opengl example", NULL, NULL);
	if (window == NULL)
		return 1;

	glfwMakeContextCurrent(window);

	//设置帧率
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}
	
	float position[6] = { -0.5f,-0.5f,
		0.0f,0.5f,
		0.5f,-0.5f };  


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

	
	{
    VertexArray va;
	VertexBuffer vb(indices_position, 4 * 2 * sizeof(float));
	  
	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);
	

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

	
		unsigned int shader = CreateShader(vertexShader, fragmentShader);
		int location = glGetUniformLocation(shader, "ourColor");
		float r = 0.0f;
		float increment = 0.05f;

		glBindVertexArray(0);
		glUseProgram(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();


			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;

			glUseProgram(shader);
			glUniform4f(location, r, 0.3f, 0.8f, 1.0f);


			va.Bind();
			ib.Bind();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			glfwSwapBuffers(window);
		}

	}
	glfwTerminate();

	return 0;
}



