#pragma once
#include <iostream>
#include "vector2.h"
//#include "matrix4.h";

namespace letc { namespace math{
	
	struct Vector3 {
		float x, y, z;

		static Vector3 One();

		Vector3();
		Vector3(const float& x, const float& y, const float&z);
		Vector3(Vector2 vector2);

		Vector3& add(const Vector3& other);
		Vector3& add(const float& other);
		Vector3& subtract(const Vector3& other);
		Vector3& subtract(const float& other);
		Vector3& multiply(const Vector3& other);
		Vector3& multiply(const float& other);
		//Vector3& multiply(const Matrix4& other);
		Vector3& divide(const Vector3& other);
		Vector3& divide(const float& other);

		Vector2 xy();
		
		Vector3& operator += (const Vector3 &other);
		Vector3& operator += (const float &other);
		Vector3& operator -= (const Vector3 &other);
		Vector3& operator -= (const float &other);
		Vector3& operator *= (const Vector3 &other);
		Vector3& operator *= (const float &other);
		//Vector3& operator *= (const Matrix4 &other);
		Vector3& operator /= (const Vector3 &other);

		bool operator == (const Vector3& other);
		bool operator != (const Vector3& other);
		
		Vector3 operator - ()const;

		friend Vector3 operator + (Vector3 left, const Vector3& right);
		friend Vector3 operator - (Vector3 left, const Vector3& right);
		friend Vector3 operator + (Vector3 left, const float& right);
		friend Vector3 operator - (Vector3 left, const float& right);
		friend Vector3 operator * (Vector3 left, const Vector3& right);
		friend Vector3 operator * (Vector3 left, const float& right);
		friend Vector3 operator / (Vector3 left, const float& right);
		friend Vector3 operator / (Vector3 left, const Vector3& right);



		friend std::ostream& operator << (std::ostream& stream, const Vector3  vector) {
			stream << "Vector3: (" << vector.x << ", " << vector.y << ", " << vector.z <<  ")";
			return stream;
		}

	};


}}
