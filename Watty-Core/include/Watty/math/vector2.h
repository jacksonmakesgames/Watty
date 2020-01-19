#pragma once
#include <iostream>

namespace letc { namespace math{
	struct Vector2 {
		float x, y;

		Vector2();
		Vector2(const float& x, const float& y);

		Vector2& add(const Vector2& other);
		Vector2& subtract(const Vector2& other);
		Vector2& multiply(const Vector2& other);
		Vector2& multiply(const float& other);
		Vector2& divide(const Vector2& other);
		Vector2& divide(const float& other);
		
		Vector2& operator += (const Vector2 &other);
		Vector2& operator -= (const Vector2 &other);
		Vector2& operator *= (const Vector2 &other);
		Vector2& operator *= (const float& other);
		Vector2& operator /= (const float& other);

		Vector2& operator /= (const Vector2 &other);

		bool operator == (const Vector2& other);
		bool operator != (const Vector2& other);

		friend Vector2 operator + (Vector2 left, const Vector2& right);
		friend Vector2 operator - (Vector2 left, const Vector2& right);
		friend Vector2 operator * (Vector2 left, const Vector2& right);
		friend Vector2 operator * (Vector2 left, const float& right);
		friend Vector2 operator / (Vector2 left, const float& right);
		friend Vector2 operator / (Vector2 left, const Vector2& right);



		friend std::ostream& operator << (std::ostream& stream, const Vector2  vector) {
			stream << "Vector2: (" << vector.x << ", " << vector.y << ")";
			return stream;
		}

	};


}}
