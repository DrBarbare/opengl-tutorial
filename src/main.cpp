#include <memory>
#include "Window.h"
#include "Cube.h"
#include "Triangle.h"
#include "Image.h"

int main(void)
{
	/* Create a windowed mode window and its OpenGL context */
	my::Window window;
	window.open(640, 480, "Hello World", nullptr, nullptr);

	// Extension loader libraries here

	auto image = my::loadBMP("resources/uvtemplate.bmp");
	my::Camera cam{my::Camera::EProjection::perspective};
	my::Triangle triangle;
	my::Cube cube;

	float angle = 0.0f;
	triangle.scale(0.5f, 0.5f, 0.0f);
	triangle.translate(1.0f, -0.0f, 0.0f);
	cube.translate(-1.0f, 0.0f, 0.0f);
	//cube.scale(0.5, 0.5, 0.5);
	while (window.isOpened())
	{
		triangle.rotate(angle, 0.0f, 0.0f, 1.0f);
		cube.rotate(angle, 0.1f, 0.1f, 0.1f);
		window.draw(cam
				, triangle
				, cube
		);
		angle += 0.5f;
		if (angle > 360) angle = 0.0f;
	}
	return 0;
}
