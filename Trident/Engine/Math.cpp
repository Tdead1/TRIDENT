#include <Math.h>
#include <cmath>

const float Math::PI = 3.1415926535f;
float Math::Clamp(float x, float i, float j) { return x > j ? j : (x < i ? i : x); }
float Math::Mod(float x, float y) { return Fract(x / y) * y; }
float Math::Fract(float x) { return x - Floor(x); }
float Math::Min(float x, float y) { return x < y ? x : y; }
float Math::Max(float x, float y) { return x > y ? x : y; }
float Math::Floor(float x) { return floor(x); }
float Math::Sqrt(float x) { return sqrt(x); }
float Math::Ceil(float x) { return floor(x) == x ? x : floor(x) + 1 * (x < 0 ? -1 : 1); }