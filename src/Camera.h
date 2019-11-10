#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

namespace my
{
class Camera
{
public:
	enum class EProjection { perspective, orthogonal };

private:

	glm::mat4 m_view;

public:

	Camera(EProjection projection);
	const glm::mat4& view() const noexcept;

};
} // namespace my

#endif // PLADEHOLDER

