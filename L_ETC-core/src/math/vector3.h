#pragma once
#include <iostream>

namespace letc { namespace math{
	struct Vector3 {
		float x, y, z;

		Vector3();
		Vector3(const float& x, const float& y, const float&z);

		Vector3& add(const Vector3& other);
		Vector3& subtract(const Vector3& other);
		Vector3& multiply(const Vector3& other);
		Vector3& divide(const Vector3& other);
		
		Vector3& operator += (const Vector3 &other);
		Vector3& operator -= (const Vector3 &other);
		Vector3& operator *= (const Vector3 &other);
		Vector3& operator /= (const Vector3 &other);

		bool operator == (const Vector3& other);
		bool operator != (const Vector3& other);

		friend Vector3 operator + (Vector3 left, const Vector3& right);
		friend Vector3 operator - (Vector3 left, const Vector3& right);
		friend Vector3 operator * (Vector3 left, const Vector3& right);
		friend Vector3 operator / (Vector3 left, const Vector3& right);



		friend std::ostream& operator << (std::ostream& stream, const Vector3  vector) {
			stream << "Vector3: (" << vector.x << ", " << vector.y << ", " << vector.z <<  ")";
			return stream;
		}

	};


}}
