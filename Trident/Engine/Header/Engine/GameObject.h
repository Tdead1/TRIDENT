#pragma once
#include <vector>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Graphics/Texture.h>

//														//
/* The base object to draw and manipulate in the world. */ 
//														//

class GameObject
{
public:
	GameObject();
	~GameObject();

	Matrix model;
	Texture texture;
	std::vector<float> fileData;
};