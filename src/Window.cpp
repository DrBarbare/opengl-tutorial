#include <GL/glew.h>
#include "Window.h"

namespace my
{

std::size_t Window::instancesCount = 0u;

Window::Window()
{
	/* Initialize the library */
	glewExperimental = true;

	if (instancesCount == 0)
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Could not initialize GLFW.");
		}
	}
	instancesCount++;

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


Window::~Window() noexcept
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
	}
	instancesCount--;
	if (instancesCount == 0)
	{
		glfwTerminate();
	}
}

void
Window::configure()
{
	glfwMakeContextCurrent(m_window);
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Could not initializa GLEW");
	}
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
}

bool
Window::isOpened() const noexcept
{
	return m_window && !glfwWindowShouldClose(m_window);
}

void
Window::step() noexcept
{
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	// TODO: Draw stuff

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
} // namespace my


