#pragma once

#include "../renderable2d.h"
#include "fontmanager.h"

namespace letc { namespace graphics {

	class Label : public Renderable2D {
	public:
		Font* m_font;
		std::string text;
		math::Vector3& position;
	public:
		Label(std::string text, float x, float y, unsigned int color);
		Label(std::string text, float x, float y, Font* font, unsigned int color);
		Label(std::string text, float x, float y, const std::string& fontName, unsigned int color);
		Label(std::string text, float x, float y, const std::string& fontName, unsigned int size, unsigned int color);
		void submit(Renderer2D* renderer)const override;
	private:
		void validateFont(const std::string& name, int size = -1);

	};


}}