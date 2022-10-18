#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererId;
	unsigned int m_Count;

public:
	IndexBuffer(const unsigned int * data, unsigned int count);
	~IndexBuffer();

	void Bind();
	void Unbind();

	inline unsigned int getCount() const { return m_Count; }
};