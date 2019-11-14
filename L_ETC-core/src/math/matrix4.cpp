#include "matrix4.h"
#include "math.h"

namespace letc {
	namespace math {

		Matrix4::Matrix4(){
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;
		}

		Matrix4::Matrix4(float diagonal){
			for (int i = 0; i < 4 * 4; i++)
				elements[i] = 0.0f;
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		Matrix4 Matrix4::identity(){
			return Matrix4(1.0f);
		}

		Matrix4& Matrix4::multiply(const Matrix4& other){
			float data[16];

			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					float sum = 0.0f;
					for (int e = 0; e < 4; e++) {
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					data[x + y * 4] = sum;
				}
			}
			memcpy(elements, data, 4 * 4 * sizeof(float));
			return *this;
		}

		Vector3 Matrix4::multiply(const Vector3& other) const
		{
			return Vector3(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
			);
		}

		Vector4 Matrix4::multiply(const Vector4& other) const
		{
			return Vector4(
				columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
				columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
				columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
				columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
			);
		}

		Matrix4& Matrix4::invert()
		{
			double temp[16];

			temp[0] = elements[5] * elements[10] * elements[15] -
				elements[5] * elements[11] * elements[14] -
				elements[9] * elements[6] * elements[15] +
				elements[9] * elements[7] * elements[14] +
				elements[13] * elements[6] * elements[11] -
				elements[13] * elements[7] * elements[10];

			temp[4] = -elements[4] * elements[10] * elements[15] +
				elements[4] * elements[11] * elements[14] +
				elements[8] * elements[6] * elements[15] -
				elements[8] * elements[7] * elements[14] -
				elements[12] * elements[6] * elements[11] +
				elements[12] * elements[7] * elements[10];

			temp[8] = elements[4] * elements[9] * elements[15] -
				elements[4] * elements[11] * elements[13] -
				elements[8] * elements[5] * elements[15] +
				elements[8] * elements[7] * elements[13] +
				elements[12] * elements[5] * elements[11] -
				elements[12] * elements[7] * elements[9];

			temp[12] = -elements[4] * elements[9] * elements[14] +
				elements[4] * elements[10] * elements[13] +
				elements[8] * elements[5] * elements[14] -
				elements[8] * elements[6] * elements[13] -
				elements[12] * elements[5] * elements[10] +
				elements[12] * elements[6] * elements[9];

			temp[1] = -elements[1] * elements[10] * elements[15] +
				elements[1] * elements[11] * elements[14] +
				elements[9] * elements[2] * elements[15] -
				elements[9] * elements[3] * elements[14] -
				elements[13] * elements[2] * elements[11] +
				elements[13] * elements[3] * elements[10];

			temp[5] = elements[0] * elements[10] * elements[15] -
				elements[0] * elements[11] * elements[14] -
				elements[8] * elements[2] * elements[15] +
				elements[8] * elements[3] * elements[14] +
				elements[12] * elements[2] * elements[11] -
				elements[12] * elements[3] * elements[10];

			temp[9] = -elements[0] * elements[9] * elements[15] +
				elements[0] * elements[11] * elements[13] +
				elements[8] * elements[1] * elements[15] -
				elements[8] * elements[3] * elements[13] -
				elements[12] * elements[1] * elements[11] +
				elements[12] * elements[3] * elements[9];

			temp[13] = elements[0] * elements[9] * elements[14] -
				elements[0] * elements[10] * elements[13] -
				elements[8] * elements[1] * elements[14] +
				elements[8] * elements[2] * elements[13] +
				elements[12] * elements[1] * elements[10] -
				elements[12] * elements[2] * elements[9];

			temp[2] = elements[1] * elements[6] * elements[15] -
				elements[1] * elements[7] * elements[14] -
				elements[5] * elements[2] * elements[15] +
				elements[5] * elements[3] * elements[14] +
				elements[13] * elements[2] * elements[7] -
				elements[13] * elements[3] * elements[6];

			temp[6] = -elements[0] * elements[6] * elements[15] +
				elements[0] * elements[7] * elements[14] +
				elements[4] * elements[2] * elements[15] -
				elements[4] * elements[3] * elements[14] -
				elements[12] * elements[2] * elements[7] +
				elements[12] * elements[3] * elements[6];

			temp[10] = elements[0] * elements[5] * elements[15] -
				elements[0] * elements[7] * elements[13] -
				elements[4] * elements[1] * elements[15] +
				elements[4] * elements[3] * elements[13] +
				elements[12] * elements[1] * elements[7] -
				elements[12] * elements[3] * elements[5];

			temp[14] = -elements[0] * elements[5] * elements[14] +
				elements[0] * elements[6] * elements[13] +
				elements[4] * elements[1] * elements[14] -
				elements[4] * elements[2] * elements[13] -
				elements[12] * elements[1] * elements[6] +
				elements[12] * elements[2] * elements[5];

			temp[3] = -elements[1] * elements[6] * elements[11] +
				elements[1] * elements[7] * elements[10] +
				elements[5] * elements[2] * elements[11] -
				elements[5] * elements[3] * elements[10] -
				elements[9] * elements[2] * elements[7] +
				elements[9] * elements[3] * elements[6];

			temp[7] = elements[0] * elements[6] * elements[11] -
				elements[0] * elements[7] * elements[10] -
				elements[4] * elements[2] * elements[11] +
				elements[4] * elements[3] * elements[10] +
				elements[8] * elements[2] * elements[7] -
				elements[8] * elements[3] * elements[6];

			temp[11] = -elements[0] * elements[5] * elements[11] +
				elements[0] * elements[7] * elements[9] +
				elements[4] * elements[1] * elements[11] -
				elements[4] * elements[3] * elements[9] -
				elements[8] * elements[1] * elements[7] +
				elements[8] * elements[3] * elements[5];

			temp[15] = elements[0] * elements[5] * elements[10] -
				elements[0] * elements[6] * elements[9] -
				elements[4] * elements[1] * elements[10] +
				elements[4] * elements[2] * elements[9] +
				elements[8] * elements[1] * elements[6] -
				elements[8] * elements[2] * elements[5];

			double det;
			det = elements[0] * temp[0] + elements[1] * temp[4] + elements[2] * temp[8] + elements[3] * temp[12];


			det = 1.0 / det;

			for (int i = 0; i < 4 * 4; i++)
				elements[i] = temp[i] * det;
			return *this;
		}


		Matrix4 operator*(Matrix4 left, const Matrix4& right){
			return left.multiply(right);
		}

		Vector3 operator*(const Matrix4& left, const Vector3& right)
		{
			return left.multiply(right);

		}

		Vector4 operator*(const Matrix4& left, const Vector4& right)
		{
			return left.multiply(right);
		}

		

		Matrix4& Matrix4::operator*=(const Matrix4 other){
			return multiply(other);
		}
		Matrix4 Matrix4::orthographic(float left, float right, float bottom, float top, float near, float far ){
			Matrix4 output(1.0f); // indentity

			output.elements[0 + 0 * 4] = 2.0f / (right - left);
			output.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			output.elements[2 + 2 * 4] = -2.0f / (far - near);

			output.elements[0 + 3 * 4] = - ((left + right) / (right - left));
			output.elements[1 + 3 * 4] = -((bottom + top) / (top - bottom));
			output.elements[2 + 3 * 4] = -((far + near)/ (far - near));

			return output;
		}

		Matrix4 Matrix4::perspective(float fov, float aspectRatio, float near, float far){
			Matrix4 output(1.0f);

			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			output.elements[0 + 0 * 4] = a;
			output.elements[1 + 1 * 4] = q;
			output.elements[2 + 2 * 4] = b;
			output.elements[3 + 2 * 4] = -1.0f;
			output.elements[2 + 3 * 4] = c;

			return output;
		}

		Matrix4 Matrix4::translation(const Vector3& translation){
			Matrix4 output(1.0f);
			output.elements[0 + 3 * 4] = translation.x;
			output.elements[1 + 3 * 4] = translation.y;
			output.elements[2 + 3 * 4] = translation.z;

			return output;
		}
		Matrix4 Matrix4::rotation(float angle, const Vector3& axis){
			Matrix4 output(1.0);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			output.elements[0 + 0 * 4] = x * omc + c;
			output.elements[1 + 0 * 4] = y * x * omc + z * s;
			output.elements[2 + 0 * 4] = x * z * omc - y * s;
			
			output.elements[0 + 1 * 4] = x * y * omc - z * s;
			output.elements[1 + 1 * 4] = y * omc + c;
			output.elements[2 + 1 * 4] = y * z * omc + x * s;

			output.elements[0 + 2 * 4] = x * z * omc + z * s;
			output.elements[1 + 2 * 4] = y * z * omc - x * s;
			output.elements[2 + 2 * 4] = z * omc + c;

			return output;
		}

		Matrix4 Matrix4::scale(const Vector3& scale){
			Matrix4 output(1.0f);
			output.elements[0 + 0 * 4] = scale.x;
			output.elements[1 + 1 * 4] = scale.y;
			output.elements[2 + 2 * 4] = scale.z;

			return output;
		}
	}
}
