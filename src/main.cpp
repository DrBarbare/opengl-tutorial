#include <memory>
#include "Window.h"

int main(void)
{
	/* Create a windowed mode window and its OpenGL context */
	my::Window window;
	window.open(640, 480, "Hello World", nullptr, nullptr);

	// Extension loader libraries here

	my::Camera cam{my::Camera::EProjection::perspective};
	my::Triangle triangle;

	float angle = 0.0f;
	triangle.scale(0.5f, 0.5f, 0.0f);
	while (window.isOpened())
	{
		triangle.rotate(angle, 0.0f, 0.0f, 1.0f);
		window.draw(cam, triangle);
		angle += 0.5f;
		if (angle > 360) angle = 0.0f;
	}
	return 0;
}
