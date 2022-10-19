#pragma once
#include<vector>
#include<GL/glew.h>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool is_normal;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:return 4;
		case GL_UNSIGNED_INT:return 4;
		case GL_UNSIGNED_BYTE:return 1;

		default:
			return 0;
			break;
		}
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout():m_Stride(0){}
	~VertexBufferLayout(){}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT,count,false });
		m_Stride += count*sizeof(GLfloat);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,false });
		m_Stride += count * sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,true });
		m_Stride += count * sizeof(GLbyte);
	}

	inline const std::vector<VertexBufferElement> GetElements()const { return m_Elements; }
	inline unsigned int GetStride()const { return m_Stride; }
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
};
