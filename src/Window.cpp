#include <GL/glew.h>
#include "Window.h"

namespace
{
const char* kVertex = R"=(
#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
void main()
{
	gl_Position.xyz = vertexPosition_modelspace;
	gl_Position.w = 1.0;
}
)=";


const char* kFragment = R"=(
#version 330 core
out vec3 color;
void main()
{
	color = vec3(1,0,0);
}
)=";
}

namespace my
{

std::size_t Window::instancesCount = 0u;

Window::Window()
{
	/* Initialize the library */
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

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		throw std::runtime_error("Could not initializa GLEW");
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	my::Shader vertex(GL_VERTEX_SHADER, kVertex);
	my::Shader fragment(GL_FRAGMENT_SHADER, kFragment);
	m_program = std::make_unique<my::GLProgram>(fragment, vertex);

	m_triangle = std::make_unique<my::Triangle>();
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
	m_program->use();
	m_triangle->draw();

	/* Swap front and back buffers */
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}
} // namespace my


