#include <iostream>
#include <Graphics/Window.h>
#include <Graphics/Resource.h>

int main()
{
	Camera cam;
	cam.Create();

	Window window;
	window.Create(&cam);
	
	GameObject obj;
	obj.fileData = Resource::LoadObject("TwoTri.obj");
	obj.texture = Resource::LoadTexture("BrickTex.png");


	bool running = true;
	while (running)
	{
		cam.Update();
		window.Draw(obj.fileData, obj.model, obj.texture);
		if (glfwGetKey(window.glfw, GLFW_KEY_E))
		{
			running = false;
		}
		window.Update();
	}
}