#include <stdexcept>
#include <iostream>
#include <iomanip>

#include <GL/glew.h>
#include "GLProgram.h"

namespace
{
template <typename Getter, typename InfoLog>
void
validateGLObject(Getter getter, InfoLog infoLog, GLenum query, GLuint id)
{
	// Check shader
	GLint status = GL_FALSE;
	getter(id, query, &status);

	GLint logLength = 0;
	getter(id, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::string log(logLength + 1, '\0');
		infoLog(id, logLength, nullptr, &log[0]);
		throw std::runtime_error(log);
	}
	else if (status != GL_TRUE)
	{
		std::cerr << "Status not ok: " << status << " / " << GL_TRUE << '\n';
		//throw std::runtime_error("Compilation failed for unknown reason.");
	}
}
} // namespace

namespace my
{

Shader::Shader(GLenum type, const char* code)
	: m_id{glCreateShader(type)},
	  m_program{nullptr}
{
	glShaderSource(m_id, 1, &code , nullptr);
	glCompileShader(m_id);
	std::cerr << "Compiling shader " << m_id << " [" << type << "]\n";
	validateGLObject(glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS, m_id);
}

Shader::~Shader()
{
	std::cerr << "Deleting shader " << m_id << '\n';
	if (m_program != nullptr)
	{
		glDetachShader(*m_program, m_id);
	}
	glDeleteShader(m_id);
}

void
Shader::attach(GLuint& program) noexcept
{
	m_program = &program;
	std::cerr << "Attaching " << m_id << " to " << *m_program << '\n';
	glAttachShader(*m_program, m_id);
}

GLuint
GLProgram::getID() noexcept
{
	return glCreateProgram();
}

void
GLProgram::link() const noexcept
{
	std::cerr << "Linking " << m_id << '\n';
	glLinkProgram(m_id);
	validateGLObject(glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS, m_id);
}

void
GLProgram::use() const noexcept
{
	glUseProgram(m_id);
}


GLuint
GLProgram::declareUniform(const char* name) const noexcept
{
	return glGetUniformLocation(m_id, name);
}

} // namespace my
