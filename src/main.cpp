#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include"render.h"
#include"shader.h"
#include <direct.h>
#include<limits.h>


#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"VertexBufferLayout.h"

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
	
	float r = 0.0f;
	float increment = 0.05f;
	Shader shader("D:/test/opengl-test/src/basic.shader");
	shader.Bind();
	shader.SetUniform4f("ourColor", r, 0.3f, 0.8f, 1.0f);

	va.Unbind();
	shader.Unbind();
	vb.Unbind();
	ib.Unbind();

	render render_obj;
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();

			render_obj.Clear();

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;

			shader.Bind();
			shader.SetUniform4f("ourColor", r, 0.3f, 0.8f, 1.0f);
			


			render_obj.Draw(va, ib, shader);

			glfwSwapBuffers(window);
		}

	}
	glfwTerminate();

	return 0;
}



