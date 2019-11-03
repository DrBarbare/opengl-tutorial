#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include <stdexcept>
#include <cstddef>
#include <utility>
#include <GLFW/glfw3.h>

namespace my
{
class Window
{
	static std::size_t instancesCount;

	GLFWwindow* m_window;
	GLuint m_vao;

	void configure();

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
	void step() noexcept;
};
} // namespace my

#endif // MY_WINDOW_H
