#ifndef MY_CUBE_H
#define MY_CUBE_H

#include <array>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include "Transformations.h"
#include "GLProgram.h"
#include "GLVector.h"
#include "Camera.h"

namespace my
{
class Cube : public Transformations<Cube>
{
	GLProgram m_program;
	GLuint m_mvpID;
	GLVector<GLfloat> m_triangles;
	GLVector<GLfloat> m_colors;

public:

	Cube();
	void draw(const Camera& cam) const;

};
} // namespace my


#endif // MY_CUBE_H

