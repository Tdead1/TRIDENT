#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <ctype.h>


// Include standard headers, Include GLEW. Always include it 
// before gl.h and glfw.h, then include GLFW.
#include <Graphics/GL/glew.h>
#include <Graphics/GL/glfw3.h>
#include <Graphics/GL/wglew.h>

#include <Graphics/Texture.h>
#include <Engine/GameObject.h>
#include <Engine/Camera.h>

class Window
{
public:
	Window();
	~Window();

	void Create(Camera* _camera);
	void Update();

	bool Draw(std::vector<GLfloat> &_data, Matrix &_model, Texture &_texture);
	void CheckGLErrors(std::string whereIsTheCheck);


	GLFWwindow* glfw;

private:
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void CreateShaders(Camera* _camera);
	GLFWwindow *InitGLFW();

	GLuint programID;
	Camera *camera;

};

