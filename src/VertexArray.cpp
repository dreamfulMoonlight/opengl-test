#include "VertexArray.h"
#include"render.h"
#include"VertexBufferLayout.h"
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	
}

void VertexArray::AddBuffer( VertexBuffer & vb, const VertexBufferLayout & layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		const auto &elelment = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elelment.count, elelment.type, elelment.is_normal, layout.GetStride(), (const void*)offset);
		offset+=elelment.count*VertexBufferElement::GetSizeOfType(elelment.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
