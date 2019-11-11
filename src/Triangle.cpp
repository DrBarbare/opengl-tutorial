#include <iostream>
#include <GL/glew.h>
#include "Triangle.h"

namespace
{
const char* kVertex = R"=(
#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
}
)=";


const char* kFragment = R"=(
#version 330 core
out vec3 color;
void main()
{
	color = vec3(1,0,0);
}
)=";

} // namespace

namespace my
{

Triangle::Triangle()
	: m_program{my::Shader(GL_VERTEX_SHADER, kVertex),
	            my::Shader(GL_FRAGMENT_SHADER, kFragment)},
	  m_mvpID{m_program.declareUniform("MVP")},
	  m_triangles({-1.0f, -1.0f, 0.0f,
	               1.0f, -1.0f, 0.0f,
	               0.0f,  1.0f, 0.0f})
{ }

void
Triangle::draw(const Camera& cam) const
{
	m_program.use();
	glUniformMatrix4fv(m_mvpID, 1, GL_FALSE, &(mvp(cam.view()))[0][0]);
	m_triangles.draw(0);
}

} // namespace my
