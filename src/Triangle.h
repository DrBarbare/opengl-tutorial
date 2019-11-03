#ifndef MY_TRIANGLE_H
#define MY_TRIANGLE_H

#include <array>
#include <GL/gl.h>

namespace my
{

class Triangle
{

	static const std::array<GLfloat, 9> vertices;
	GLuint m_buffer;

puiblic:

	Triangle();
	void draw();
};

} // namespace my