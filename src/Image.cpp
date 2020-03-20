#include <fstream>
#include <iterator>
#include <cstring>
#include <stdexcept>

#include "Image.h"

namespace
{

GLuint
getID()
{
	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	return id;
}

} // namespace

namespace my
{

void
Image::upload() const noexcept
{
	glTexImage2D(
		GL_TEXTURE_2D,
		0, GL_RGB,
		m_dimensions.width().value,
		m_dimensions.height().value,
		0, GL_BGR,
		GL_UNSIGNED_BYTE,
		m_data.get()
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

Image::Image(Dimensions dimensions)
: m_dimensions{std::move(dimensions)},
  m_data{new byte_type[m_dimensions.size()]},
  m_id{getID()}
{}

Image::Image(Dimensions dimensions, const byte_type* data)
: m_dimensions{std::move(dimensions)},
  m_data{new byte_type[m_dimensions.size()]},
  m_id{getID()}
{
	std::copy_n(data, m_dimensions.size(), m_data.get());
	upload();
}


Image::byte_type*
Image::data() noexcept
{
	return m_data.get();
}


Image
loadBMP(const char* file)
{
	std::ifstream stream(file, std::ios::binary);

	if (!stream)
	{
		throw std::runtime_error("Failed to load BMP file");
	}

	constexpr std::size_t bmpHeaderSize = 54;
	char header[bmpHeaderSize];
	const auto read = stream.readsome(header, bmpHeaderSize);

	if (read != bmpHeaderSize)
	{
		throw std::runtime_error("Could not read BMP Header");
	}

	if (std::strncmp(header, "BM", 2) != 0)
	{
		throw std::runtime_error("File not a BMP file");
	}

	std::size_t dataOffset = *(reinterpret_cast<int*>(&header[0x0A]));
	std::size_t imageSize  = *(reinterpret_cast<int*>(&header[0x22]));
	std::size_t width      = *(reinterpret_cast<int*>(&header[0x12]));
	std::size_t height     = *(reinterpret_cast<int*>(&header[0x16]));

	if (imageSize == 0) imageSize = width * height * 3;
	if (dataOffset == 0) dataOffset = bmpHeaderSize;

	std::size_t depth = imageSize / (width * height);

	Image image{Dimensions{Width{width}, Height{height}, Depth{depth}}};

	std::copy_n(std::istream_iterator<Image::byte_type>(stream), imageSize, image.data());
	image.upload();

	return image;
}

} // namespace my
