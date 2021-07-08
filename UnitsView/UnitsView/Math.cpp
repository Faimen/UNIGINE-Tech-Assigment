#include "Math.h"

MyMath::Vector2::Vector2()
{
	x = y = 0;
}

MyMath::Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

MyMath::Vector2::Vector2(const Vector2& vector)
{
	x = vector.x;
	y = vector.y;
}

MyMath::Vector2::~Vector2() {}

float MyMath::Vector2::Angle(Vector2 &vec1, Vector2 &vec2)
{
	return atan2f(fabs(CrossProduct(vec1, vec2)), DotProduct(vec1, vec2)) * 180.0f / pi;
}

MyMath::Vector2 MyMath::Vector2::Normalized()
{
	float len = Length(x, y);

	return Vector2(x / len, y / len);
}

MyMath::Vector2 MyMath::operator-(const Vector2& left, const Vector2& right)
{
	return Vector2(left.x - right.x, left.y - right.y);
}

MyMath::Vector2 MyMath::operator*(const Vector2& left, const float value)
{
	return Vector2(left.x * value, left.y * value);
}

float MyMath::DotProduct(Vector2 &vec1, Vector2 &vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}

float MyMath::CrossProduct(Vector2 &vec1, Vector2 &vec2)
{
	return vec1.x * vec2.y + vec1.y * vec2.x;
}

float MyMath::Sqrt(float squared)
{
	static int csr = 0;
	if (!csr) csr = _mm_getcsr() | 0x8040; //DAZ,FTZ (divide by zero=0)
	_mm_setcsr(csr);
	return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(squared))) * squared;
}

float MyMath::Length(float x, float y)
{
	return MyMath::Sqrt(x * x + y * y);
}
