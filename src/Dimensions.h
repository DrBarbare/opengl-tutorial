#ifndef MY_DIMENSIONS_H
#define MY_DIMENSIONS_H

#include <cstddef>

#include "Comparisons.h"

namespace my
{

struct Width : public SimpleOrderOperators<Width>, public AddOrderOperators<Width>
{
	constexpr explicit Width(std::size_t v) : value{v} {}
	std::size_t value;
};

struct Height : public SimpleOrderOperators<Height>, public AddOrderOperators<Height>
{
	constexpr explicit Height(std::size_t v) : value{v} {}
	std::size_t value;
};

struct Depth : public SimpleOrderOperators<Depth>, public AddOrderOperators<Depth>
{
	constexpr explicit Depth(std::size_t v) : value{v} {}
	std::size_t value;
};

class Dimensions
{
	Width m_width;
	Height m_height;
	Depth m_depth;

public:
	constexpr Dimensions(Width w, Height h) : m_width{w}, m_height{h}, m_depth{Depth{0}} {}
	constexpr Dimensions(Width w, Height h, Depth d) : m_width{w}, m_height{h}, m_depth{d} {}

	constexpr decltype(auto) width() const noexcept { return m_width; }
	constexpr decltype(auto) height() const noexcept { return m_height; }
	constexpr decltype(auto) depth() const noexcept { return m_depth; }

	constexpr bool operator==(Dimensions const& rhs) const noexcept
	{
		return
			width() == rhs.width()
			&& height() == rhs.height()
			&& depth() == rhs.depth();
	}

	constexpr std::size_t size() const noexcept
	{
		return m_width.value * m_height.value * m_depth.value;
	}
};
}

#endif // MY_DIMENSIONS_H

