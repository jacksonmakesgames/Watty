#pragma once
#include <glm.hpp>
#include <random>

namespace letc { namespace graphics {

	typedef union WattyColor
	{
		
		unsigned int      c = 0;    // packed representation
		struct abgrTag	          // component-wise representation
		{
			unsigned char a = 0;
			unsigned char b = 0;    // (reversed for intel storage order)
			unsigned char g = 0;
			unsigned char r = 0;
		} rgba;



		float asFloat[4];

		WattyColor(unsigned int ui) {
			c = ui;
		}
		
		WattyColor(float red, float green, float blue, float alpha) {
			rgba.r = red;
			rgba.g = green;
			rgba.b = blue;
			rgba.a = alpha;
		}
		WattyColor() {
			c = 0;
		}

	} WATTYCOLOR;

	struct Color
	{

		

		//float r, g, b, a = 0;

		static WattyColor black;
		static WattyColor white;
		static WattyColor red;
		static WattyColor blue;
		static WattyColor green;
		static WattyColor pink;
		static WattyColor purple;
		static WattyColor orange;
		static WattyColor brown;
		static WattyColor yellow;

		static WattyColor RGB(glm::vec3 color) {
			int	r = color.x * 255.0f;
			int	g = color.y * 255.0f;
			int	b = color.z * 255.0f;
			int	a = 255.0f;
			
			WattyColor out = WattyColor(a << 24 | b << 16 | g << 8 | r);
			return out;
		}

	static WattyColor RGBA(glm::vec4 color) {
			int	r = color.x * 255.0f;
			int	g = color.y * 255.0f;
			int	b = color.z * 255.0f;
			int	a = color.w * 255.0f;

			WattyColor out = WattyColor(a << 24 | b << 16 | g << 8 | r);
			return out;
	}
	static 	WattyColor RGBA(float red, float green, float blue, float alpha) {
			int	r = red * 255.0f;
			int	g = green * 255.0f;
			int	b = blue * 255.0f;
			int	a = alpha * 255.0f;
			WattyColor out = WattyColor(a << 24 | b << 16 | g << 8 | r);
			return out;
	}
	static 	WattyColor RGB(float red, float green, float blue) {
			int	r = red * 255.0f;
			int	g = green * 255.0f;
			int	b = blue * 255.0f;
			int	a = 255.0f;
			WattyColor out = WattyColor(a << 24 | b << 16 | g << 8 | r);
			return out;
	}
	
	static WattyColor random() {
		int	r = rand() * 255.0f;
		int	g = rand() * 255.0f;
		int	b = rand() * 255.0f;
		int	a = rand() * 255.0f;
		WattyColor out = WattyColor(a << 24 | b << 16 | g << 8 | r);
		return out;
	}

	static WattyColor lerp(WattyColor colorA, WattyColor colorB, float t) {
		float r, g, b, a = 0;

		r = (1 - t) * colorA.rgba.r + t * colorB.rgba.r;
		g = (1 - t) * colorA.rgba.g + t * colorB.rgba.g;
		b = (1 - t) * colorA.rgba.b + t * colorB.rgba.b;
		a = (1 - t) * colorA.rgba.a + t * colorB.rgba.a;

		WattyColor out = WattyColor(r,g,b,a);
		return out;
	}

	};

	
} }