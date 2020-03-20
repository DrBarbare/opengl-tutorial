#ifndef MY_IMAGE_H
#define MY_IMAGE_H

#include <memory>
#include <algorithm>
#include <GL/gl.h>
#include "Dimensions.h"

namespace my
{

class Image
{

public:
	using byte_type = std::uint8_t;

private:
	Dimensions m_dimensions;
	std::unique_ptr<byte_type[]> m_data;
	GLuint m_id;

public:

	Image() = default;
	Image(Dimensions dimensions);
	Image(Dimensions dimensions, const byte_type* data);

	byte_type* data() noexcept;
	void upload() const noexcept;
};

Image loadBMP(const char*);

} // namespace my

#endif // MY_IMAGE_H

