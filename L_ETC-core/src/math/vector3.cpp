#include "Vector3.h"
namespace letc {namespace math {
	Vector3 Vector3::One()
	{
		return Vector3(1,1,1);
	}
	math::Vector3::Vector3(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	math::Vector3::Vector3(const float& x, const float& y, const float& z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3& math::Vector3::add(const Vector3& other){
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector3& math::Vector3::subtract(const Vector3& other){
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector3& math::Vector3::multiply(const Vector3& other){
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	/*Vector3& math::Vector3::multiply(const Matrix4& other){
	
		x = other.columns[0].x * x + other.columns[1].x * y + other.columns[2].x * z + other.columns[3].x;
		y = other.columns[0].y * x + other.columns[1].y * y + other.columns[2].y * z + other.columns[3].y;
		z = other.columns[0].z * x + other.columns[1].z * y + other.columns[2].z * z + other.columns[3].z;
		
		return *this;
	}*/

	Vector3& Vector3::multiply(const float& other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}
	Vector3& Vector3::divide(const float& other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	Vector2 Vector3::xy()
	{
		return Vector2(x, y);
	}

	Vector3& math::Vector3::divide(const Vector3& other){
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& other){
		return add(other);
	}

	Vector3& Vector3::operator-=(const Vector3& other){
		return subtract(other);
	}

	Vector3& Vector3::operator*=(const Vector3& other){
		return multiply(other);
	}
	Vector3& Vector3::operator*=(const float& other){
		return multiply(other);
	}

	/*Vector3& Vector3::operator*=(const Matrix4& other){
		return multiply(other);
	}*/

	Vector3& Vector3::operator/=(const Vector3& other){
		return divide(other);
	}

	bool Vector3::operator==(const Vector3& other){
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vector3::operator!=(const Vector3& other){
		return !(*this == other);
	}

	Vector3 Vector3::operator-() const
	{
			Vector3 v;
			v.x = -x;
			v.y = -y;
			v.z = -z;
			return v;
	}

	Vector3 operator+(Vector3 left, const Vector3& right){
		return left.add(right);
		
	}
	Vector3 operator-(Vector3 left, const Vector3& right){
		return left.subtract(right);
		
	}
	Vector3 operator*(Vector3 left, const Vector3& right){
		return left.multiply(right);
		
	}
	Vector3 operator*(Vector3 left, const float& right)
	{
		return left.multiply(right);
	}
	Vector3 operator/(Vector3 left, const float& right)
	{
		return left.divide(right);
	}
	Vector3 operator/(Vector3 left, const Vector3& right){
		return left.divide(right);
		
	}
	
}

}
