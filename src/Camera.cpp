#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

namespace my
{

Camera::Camera(EProjection projection)
	: m_view{ (projection == EProjection::perspective ?
		glm::perspective(glm::radians(30.0f), 4.0f/3.0f, 0.1f, 100.0f)
		: glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f))
		* glm::lookAt(
			glm::vec3(4, 3, 3),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
	)}
{ }

const glm::mat4&
Camera::view() const noexcept
{
	return m_view;
}

} // namespace my


