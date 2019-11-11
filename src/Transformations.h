#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace my
{
template <typename Derived>
class Transformations
{
	Derived* m_self;
	glm::mat4 m_translation;
	glm::mat4 m_rotation;
	glm::mat4 m_scale;
	mutable glm::mat4 m_mvp;
	mutable bool m_recomputeModel;

protected:

	Transformations();
	glm::mat4 mvp(const glm::mat4& view) const noexcept;

public:

	Derived& translate(float x, float y, float z) noexcept;
	Derived& rotate(float degrees, float x, float y, float z) noexcept;
	Derived& scale(float fx, float fy, float fz) noexcept;
};
} // namespace my

#include "Transformations.impl"

#endif // PLADEHOLDER
