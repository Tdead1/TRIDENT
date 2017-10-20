#pragma once

#include <Math/Vector.h>

#include <cmath>

#include <string>

struct Matrix
{
	union
	{
		float m[4][4];

		float f[16];

		struct
		{
			Vec3 xAxis;

			float wx;

			Vec3 yAxis;

			float wy;

			Vec3 zAxis;

			float wz;

			Vec3 translation;

			float one;
		};
	};

	//! Construct a new matrix from explicit values

	Matrix(float m00, float m01, float m02, float m03,

		float m10, float m11, float m12, float m13,

		float m20, float m21, float m22, float m23,

		float m30, float m31, float m32, float m33);

	//! Construct a new identity matrix

	Matrix();

	//! Transform the given vector by this matrix.

	Vec3 operator*(const Vec3& vec) const;

	Vec4 operator*(const Vec4& vec) const;

	Matrix operator+(const Matrix& mat) const;

	Matrix operator-(const Matrix& mat) const;

	Matrix operator*(const Matrix& mat) const;

	//! Translation bit of the matrix

	Vec3 GetTranslation() const;

	//! Set the transltion of the matrix

	void SetTranslation(const Vec3& vec);

	//! Get the x orientation axis

	Vec3 GetXAxis() const;

	//! Get the y orientation axis

	Vec3 GetYAxis() const;

	//! Get the z orientation axis

	Vec3 GetZAxis() const;

	//! Get the determinant of this matrix

	float Determinant() const;

	//! Inverts this matrix

	bool Invert();

	//! Transposes this matrix

	void Transpose();

	//! Sets the orientation of the matrix to the orthogonal basis vector

	//! It perfoms no checks on the orthogonality!

	//!

	//! @param x X orthogonal basis vector

	//! @param y Y orthogonal basis vector

	//! @param z Z orthogonal basis vector

	void SetOrientation(const Vec3& x, const Vec3& y, const Vec3& z);

	//! Set orientation using Euler angles. Broken at current!

	static Matrix CreateEulerAxis(float yaw, float pitch, float roll);

	//! Creates an identity matrix

	static Matrix CreateIdentity();

	//! Creates an matrix based on a position, scale and rotation.

	static Matrix CreateModel(Vec3 pos, Vec3 rot, Vec3 scale);

	//! Creates an matrix based on a position, scale and rotation (in degrees).

	static Matrix CreateModelDeg(Vec3 pos, Vec3 drot, Vec3 scale);

	//! Creates a transation matrix

	static Matrix CreateTranslation(Vec3 pos);

	//! Creates a scale matrix

	static Matrix CreateScale(Vec3 scale);

	//! Creates a rotation matrix around an arbitrary axis

	static Matrix CreateRotate(float angle, const Vec3& axis);

	//! Angle in radians

	static Matrix CreateRotateX(float angle);

	//! Angle in radians

	static Matrix CreateRotateY(float angle);

	//! Angle in radians

	static Matrix CreateRotateZ(float angle);

	//! Creates an orthographic projection matrix

	static Matrix CreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);

	//! Creates a frustum projection matrix

	static Matrix CreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ);

	//! Creates a perspective projection matrix from camera settings

	static Matrix CreatePerspective(float fovy, float aspect, float nearZ, float farZ);

	//! Creates a look at matrix, usualy a view matrix

	static Matrix CreateLookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

	//! Transfrom just the direction

	Vec3 TransformDirectionVector(const Vec3& direction);

	std::string Print();
};