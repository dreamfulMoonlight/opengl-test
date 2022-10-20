#include "shader.h"


ShaderProgramSource Shader::ParseShader(const std::string&file_path) {
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::ifstream stream(file_path);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(),ss[1].str() };
}


Shader::Shader(const std::string & filename):m_FilePath(filename),m_RendererId(0)
{
	ShaderProgramSource source = ParseShader(filename);
	m_RendererId = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererId));
}

void Shader::Bind() const
{
	glUseProgram(m_RendererId);
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string name, float v0, float v1, float f2, float f3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, f2, f3);
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	//check
	int success;
	GLchar infoLog[512];
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
	if (success == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char *message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, infoLog));
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << (type == GL_VERTEX_SHADER ? "vertex:" : "fragment:") << infoLog << std::endl;
		GLCall(glDeleteShader(id));
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader );

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));


	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

unsigned int Shader::GetUniformLocation(const std::string & name)
{
	if (m_locationCache.find(name) != m_locationCache.end())
		return m_locationCache[name];

	int location = glGetUniformLocation(m_RendererId, name.c_str());
	if (location == -1)
		std::cout << "Warning:unform" << name << "doesn't exist!" << std::endl;
	return location;
}

