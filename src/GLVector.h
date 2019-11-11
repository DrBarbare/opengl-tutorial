#ifndef MY_GL_VECTOR_H
#define MY_GL_VECTOR_H

#include <iostream>
#include <memory>
#include <cstddef>
#include <GL/gl.h>

namespace my
{

namespace detail
{
	template <typename T>
	constexpr decltype(auto)
	toGLType();

	template <>
	constexpr decltype(auto)
	toGLType<GLfloat>()
	{
		return GL_FLOAT;
	}

} // namespace detail

template <typename T>
class GLVector
{
	static constexpr GLuint vertexSize = 3;
	std::size_t m_size;
	std::unique_ptr<T[]> m_data;
	GLuint m_id;

public:
	template <std::size_t N>
	GLVector(const T (&data)[N])
	: m_size{N}, m_data{new T[N]}
	{
		std::copy(&data[0], &data[0]+N, m_data.get());
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, N * sizeof(T), m_data.get(), GL_STATIC_DRAW);
	}


	void
	configure(GLuint attribute) const noexcept
	{
		glEnableVertexAttribArray(attribute);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glVertexAttribPointer(
				attribute,
				vertexSize,
				GL_FLOAT, //detail::toGLType<T>(),           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
				);
	}

	void
	draw(GLuint attribute) const noexcept
	{
		configure(attribute);
		glDrawArrays(GL_TRIANGLES, 0, m_size / vertexSize);
		glDisableVertexAttribArray(attribute);
	}

};

} // namespace my

#endif // MY_GL_VECTOR_H

