#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
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
// An array of 3 vectors which represents 3 vertices
const std::array<GLfloat, 9> Triangle::vertices = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f
};

Triangle::Triangle()
	: m_program{my::Shader(GL_VERTEX_SHADER, kVertex),
	            my::Shader(GL_FRAGMENT_SHADER, kFragment)},
	  m_mvpID{m_program.declareUniform("MVP")},
	  m_translation{glm::translate(glm::vec3(0.0f, 0.0f, 0.0f))},
	  m_rotation{glm::rotate(glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f))},
	  m_scale{glm::scale(glm::vec3(1.0f, 1.0f, 1.0f))},
	  m_mvp{glm::mat4(1.0f)},
	  m_recomputeModel{true}
{

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &m_buffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
}

void
Triangle::draw(const Camera& cam) const
{
	m_program.use();
	glUniformMatrix4fv(m_mvpID, 1, GL_FALSE, &(mvp(cam))[0][0]);
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glVertexAttribPointer(
	   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
	   3,                  // size
	   GL_FLOAT,           // type
	   GL_FALSE,           // normalized?
	   0,                  // stride
	   (void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

glm::mat4
Triangle::mvp(const Camera& cam) const noexcept
{
	if (m_recomputeModel)
	{
		m_mvp = cam.view()
		        * m_translation
		        * m_rotation
		        * m_scale;
		m_recomputeModel = false;
	}

	return m_mvp;
}

Triangle&
Triangle::translate(float x, float y, float z) noexcept
{
	m_translation = glm::translate(glm::vec3(x, y, z));
	m_recomputeModel = true;
	return *this;
}

Triangle&
Triangle::rotate(float degrees, float x, float y, float z) noexcept
{
	m_rotation = glm::rotate(glm::radians(degrees), glm::vec3(x, y, z));
	m_recomputeModel = true;
	return *this;
}

Triangle&
Triangle::scale(float fx, float fy, float fz) noexcept
{
	m_scale = glm::scale(glm::vec3(fx, fy, fz));
	m_recomputeModel = true;
	return *this;
}

} // namespace my
