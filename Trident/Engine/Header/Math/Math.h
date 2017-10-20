#pragma once

class Math {
public:

	static const float PI;

	//! Fast absolute calculation for floats.
	inline static float fabsf(float f) { return (f < 0) ? -f : f; }

	//! Fast absolute calculation for ints.
	inline static int fabsi(int i) { return (i < 0) ? -i : i; }

	static float mClamp(float x, float i, float j);
	static float mMod(float x, float y);
	static float mFloor(float x);
	static float mFract(float x);
	static float mMin(float x, float y);
	static float mMax(float x, float y);
	static float mSqrt(float x);
	static float mCeil(float x);
};