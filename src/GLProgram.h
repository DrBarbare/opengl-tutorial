#ifndef MY_GL_PROGRAM_H
#define MY_GL_PROGRAM_H

#include <memory>
#include <GL/gl.h>
#include "unused.h"

namespace my
{

class Shader
{
	GLuint m_id;
	GLuint* m_program;

public:

	explicit Shader(GLenum type, const char* code);
	~Shader();
	void attach(GLuint& program) noexcept;

};

class GLProgram
{
	GLuint m_id;
	void link() const noexcept;

	static GLuint getID() noexcept;

public:

	template <typename... Shaders>
	GLProgram(Shaders&&... shaders)
	: m_id(getID())
	{
		// Attach all shaders in turn
		my::unused((std::forward<Shaders>(shaders).attach(m_id), 0)...);

		link();
	}

	void use() const noexcept;

	GLuint declareUniform(const char* name) const noexcept;
};

} // namespace my

#endif // MY_GL_PROGRAM_H


