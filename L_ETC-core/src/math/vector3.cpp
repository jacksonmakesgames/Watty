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

	Vector3& Vector3::operator/=(const Vector3& other){
		return divide(other);
	}

	bool Vector3::operator==(const Vector3& other){
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vector3::operator!=(const Vector3& other){
		return !(*this == other);
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
