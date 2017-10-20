#include <Math/Math.h>
#include <cmath>

const float Math::PI = 3.1415926535f;

float Math::mClamp(float x, float i, float j) { return x > j ? j : (x < i ? i : x); }

float Math::mMod(float x, float y) { return mFract(x / y) * y; }

float Math::mFract(float x) { return x - mFloor(x); }

float Math::mMin(float x, float y) { return x < y ? x : y; }

float Math::mMax(float x, float y) { return x > y ? x : y; }

float Math::mFloor(float x) { return floor(x); }

float Math::mSqrt(float x) { return sqrt(x); }

float Math::mCeil(float x) { return floor(x) == x ? x : floor(x) + 1 * (x < 0 ? -1 : 1); }