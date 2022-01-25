#pragma once
#include <iostream>

namespace watty { namespace math{
	struct Vector4 {
		float x, y, z, w;

		Vector4() = default;
		Vector4(const float& x, const float& y, const float& z, const float& w);

		Vector4& add(const Vector4& other);
		Vector4& subtract(const Vector4& other);
		Vector4& multiply(const Vector4& other);
		Vector4& divide(const Vector4& other);
		
		Vector4& operator += (const Vector4 &other);
		Vector4& operator -= (const Vector4 &other);
		Vector4& operator *= (const Vector4 &other);
		Vector4& operator /= (const Vector4 &other);

		bool operator == (const Vector4& other);
		bool operator != (const Vector4& other);

		friend Vector4 operator + (Vector4 left, const Vector4& right);
		friend Vector4 operator - (Vector4 left, const Vector4& right);
		friend Vector4 operator * (Vector4 left, const Vector4& right);
		friend Vector4 operator / (Vector4 left, const Vector4& right);



		friend std::ostream& operator << (std::ostream& stream, const Vector4  vector) {
			stream << "Vector4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}

	};


}}
