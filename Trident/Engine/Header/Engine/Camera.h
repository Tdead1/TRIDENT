#pragma once
#include <Engine/GameObject.h>

class Camera : public GameObject
{
public:
	Camera();
	~Camera();

	void Create();
	void Update();

	Vec3 position;

	Matrix view;
	Matrix proj;
	Matrix pv;
};

