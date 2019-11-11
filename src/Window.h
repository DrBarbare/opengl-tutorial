#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include <functional>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <utility>

#include <GLFW/glfw3.h>

#include "Camera.h"
#include "unused.h"


namespace my
{
class Window
{
	static std::size_t instancesCount;

	GLFWwindow* m_window;
	GLuint m_vao;
	void configure();

	std::vector<std::function<void(void)>> m_actions;
	template <typename Drawable>
	void
	wrap(const Camera& cam, const Drawable& drawable)
	{
		m_actions.emplace_back([&cam, &drawable]() { return drawable.draw(cam); });
	}

	void draw();

public:

	Window();
	~Window() noexcept;
	Window(Window&&) = default;
	Window(Window const&) = delete;
	Window& operator=(Window&&) = default;
	Window& operator=(Window const&) = delete;

	template <typename... Args>
	Window& open(Args&& ... args)
	{
		m_window = glfwCreateWindow(std::forward<Args>(args)...);

		if (m_window)
		{
			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
			configure();
		}
		else
		{
			throw std::runtime_error("Could not open GLFW window.");
		}

		return *this;
	}

	template <typename... Args>
	static Window create(Args&& ... args)
	{
		Window w;
		w.open(std::forward<Args>(args)...);
		return w;
	}

	bool isOpened() const noexcept;

	template <typename... Drawables>
	void draw(const Camera& cam, const Drawables& ... drawables)
	{
		// Prepare drawing routines
		my::unused((wrap(cam, drawables),0)...);
		draw();
	}
};
} // namespace my

#endif // MY_WINDOW_H
