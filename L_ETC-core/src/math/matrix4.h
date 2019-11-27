#pragma once
#include "vector3.h"
#include "vector4.h"
#include "math_functions.h"
#include <iomanip>


namespace letc {namespace math {
	struct Matrix4 {
		union {
			float elements[4 * 4];
			Vector4 columns[4];
		};

		Matrix4();
		Matrix4(float diagonal);

		static Matrix4 identity();
		static Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static Matrix4 perspective(float fov, float aspectRatio, float near, float far);

		static Matrix4 translation(const Vector3& translation);
		static Matrix4 rotation(float angle, const Vector3& axis);
		static Matrix4 rotationAroundPoint(const Vector3& point,float angle , const Vector3& axis);
		static Matrix4 scale(const Vector3& scale);

		Matrix4& multiply(const Matrix4& other);


		friend Matrix4 operator * (Matrix4 left, const Matrix4& right);
		Matrix4& operator *= (const Matrix4 other);
		
		Vector3 multiply(const Vector3& other) const;
		Vector4 multiply(const Vector4& other) const;

		friend Vector3 operator * (const Matrix4& left, const Vector3& right);
		friend Vector4 operator * (const Matrix4& left, const Vector4& right);

		const bool isEmpty() const;

		Matrix4& invert();
		
		friend std::ostream& operator<<(std::ostream& stream, const Matrix4 matrix)
		{
			stream << "Matrix4: [" << std::endl;
			for (int i = 0; i < 4; i++) { // columns
				for (int j = 0; j < 4; j++) { // rows
					stream << "\t" << std::setprecision(2) << std::fixed << matrix.elements[j + i * 4] << ",\t";
				}
				stream << std::endl;
			}
			stream << "         ]";
			return stream;
		}
	};
	
	
}}