#pragma once
#include "cmath"
#include <intrin.h>
#include <xmmintrin.h>

namespace MyMath
{
	const float pi = 3.141593f;
	const float halfpi = 1.570796f;
	const float quarterpi = 0.7853982f;

	class Vector2 
	{
	public:
		Vector2();
		Vector2(float x, float y);
		Vector2(const Vector2& vector);

		~Vector2();

		static float Angle(Vector2& vec1, Vector2& vec2);
		Vector2 Normalized();

		float x;
		float y;
	};

	Vector2 operator -(const Vector2& left, const Vector2& right);
	Vector2 operator*(const Vector2& left, const float value);

	float DotProduct(Vector2 &vec1, Vector2& vec2);
	float CrossProduct(Vector2& vec1, Vector2& vec2);
	float Sqrt(float squared);
	float Length(float x, float y);
}