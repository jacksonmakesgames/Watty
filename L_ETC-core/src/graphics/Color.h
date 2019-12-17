#pragma once
#include "../math/vector3.h"
#include "../math/vector4.h"
#include <random>

namespace letc { namespace graphics {

	static struct Color
	{
		static unsigned int red;
		static unsigned int blue;
		static unsigned int green;
		static unsigned int pink;
		static unsigned int purple;
		static unsigned int orange;
		static unsigned int brown;
		static unsigned int white;

		static unsigned int RGB(math::Vector3 color) {
			int	r = color.x * 255.0f;
			int	g = color.y * 255.0f;
			int	b = color.z * 255.0f;
			int	a = 255.0f;
			return a << 24 | b << 16 | g << 8 | r;
		}

	static 	unsigned int RGBA(math::Vector4 color) {
			int	r = color.x * 255.0f;
			int	g = color.y * 255.0f;
			int	b = color.z * 255.0f;
			int	a = color.w * 255.0f;
			return a << 24 | b << 16 | g << 8 | r;
	}
	static 	unsigned int RGBA(float red, float green, float blue, float alpha) {
			int	r = red * 255.0f;
			int	g = green * 255.0f;
			int	b = blue * 255.0f;
			int	a = alpha * 255.0f;
			return a << 24 | b << 16 | g << 8 | r;
	}
	static 	unsigned int RGB(float red, float green, float blue) {
			int	r = red * 255.0f;
			int	g = green * 255.0f;
			int	b = blue * 255.0f;
			int	a = 255.0f;
			return a << 24 | b << 16 | g << 8 | r;
	}
	
	static unsigned int random() {
		int	r = rand() * 255.0f;
		int	g = rand() * 255.0f;
		int	b = rand() * 255.0f;
		int	a = rand() * 255.0f;
		return a << 24 | b << 16 | g << 8 | r;
	}

	};

	//								AABBGGRR
	unsigned int Color::red		= 0xFF0000ff;
	unsigned int Color::blue	= 0xFFff0000;
	unsigned int Color::green	= 0xFF00FF00;
	unsigned int Color::pink	= 0xffff00ff;
	unsigned int Color::orange	= 0xff00a5ff;
	unsigned int Color::purple	= 0xffad0d6a;
	unsigned int Color::brown	= 0xff13458b;
	unsigned int Color::white	= 0xffffffff;

} }