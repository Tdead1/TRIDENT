#pragma once

class Math {

public:
	static const float PI;

	//! Fast absolute calculation for floats.
	inline static float fabsf(float f) { return (f < 0) ? -f : f; }
	//! Fast absolute calculation for ints.
	inline static int fabsi(int i) { return (i < 0) ? -i : i; }

	static float Clamp(float x, float i, float j);
	static float Mod(float x, float y);
	static float Floor(float x);
	static float Fract(float x);
	static float Min(float x, float y);
	static float Max(float x, float y);
	static float Sqrt(float x);
	static float Ceil(float x);

};