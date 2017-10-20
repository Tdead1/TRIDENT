#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <ctype.h>
#include <Graphics/Texture.h>

#include <Graphics/GL/glew.h>

using namespace std;


class Resource
{
public:
	Resource();
	~Resource();
	
	static std::vector<GLfloat> LoadObject(std::string fileName);
	static Texture LoadTexture(std::string path);
};

