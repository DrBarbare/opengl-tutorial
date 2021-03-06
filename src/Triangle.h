#ifndef MY_TRIANGLE_H
#define MY_TRIANGLE_H

#include <array>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "Transformations.h"
#include "GLProgram.h"
#include "Camera.h"
#include "GLVector.h"

namespace my
{

class Triangle : public Transformations<Triangle>
{
	GLProgram m_program;
	GLuint m_mvpID;
	GLVector<GLfloat> m_triangles;

public:

	Triangle();
	void draw(const Camera& cam) const;

};

} // namespace my

#endif // MY_TRIANGLE_H
