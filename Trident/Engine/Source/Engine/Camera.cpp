#include <Engine/Camera.h>

Camera::Camera(){}
Camera::~Camera(){}

void Camera::Create()
{
	position = Vec3(10, 0, 10);
}

void Camera::Update()
{
	proj = Matrix::CreatePerspective(0.7f, 16.f / 9.f, 0.1f, 100.0f);
	
	view = Matrix::CreateLookAt(
		position,		// position
		Vec3(0, 0, 0),	// origin
		Vec3(0, 1, 0)	// up
	);

	pv = proj * view;
}
