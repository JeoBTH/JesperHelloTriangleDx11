#include <Windows.h>
#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Window window(800, 600); // Create a desktop window
	Renderer renderer(window); // Initialize Direct3D 11
	// Frame buffer. RenderTargetView & Buffer Swapping on the update loop
	// Vertex buffer for our triangle
	Triangle triangle(renderer);
	// Vertex Shader, Pixel Shader for our triangle
	// Specify Input Layout to bind our Vertex Buffer to the Vertex Shader. And define the viewport

	MSG msg = { 0 };

	while(true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}

		// Draw
		renderer.beginFrame();
		// Render all your stuff!
		triangle.draw(renderer);
		renderer.endFrame(); // put the result on the screen, by swapping the buffers


	}

	return 0;
}