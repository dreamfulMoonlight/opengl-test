#pragma once

#include<GL/glew.h>
#include<iostream>
#include"VertexArray.h"
#include"IndexBuffer.h"
#include"shader.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


class render
{
public:
	void Clear();
	void Draw(VertexArray &va,  IndexBuffer &ib, Shader &shade);
};

