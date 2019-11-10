#ifndef MY_TRIANGLE_H
#define MY_TRIANGLE_H

#include <array>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "GLProgram.h"
#include "Camera.h"

namespace my
{

class Triangle
{
	GLProgram m_program;
	GLuint m_mvpID;
	static const std::array<GLfloat, 9> vertices;
	GLuint m_buffer;

	glm::mat4 m_translation;
	glm::mat4 m_rotation;
	glm::mat4 m_scale;
	mutable glm::mat4 m_mvp;
	mutable bool m_recomputeModel;

	glm::mat4 mvp(const Camera& cam) const noexcept;

public:

	Triangle();
	void draw(const Camera& cam) const;

	Triangle& translate(float x, float y, float z) noexcept;
	Triangle& rotate(float degrees, float x, float y, float z) noexcept;
	Triangle& scale(float fx, float fy, float fz) noexcept;
};

} // namespace my

#endif // MY_TRIANGLE_H
