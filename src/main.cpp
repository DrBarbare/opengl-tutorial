#include <memory>
#include <glm/glm.hpp>
#include "Window.h"

int main(void)
{
	/* Create a windowed mode window and its OpenGL context */
	my::Window window;
	window.open(640, 480, "Hello World", nullptr, nullptr);

	// Extension loader libraries here

	/* Loop until the user closes the window */
	while (window.isOpened())
	{
		window.step();
	}
	return 0;
}
