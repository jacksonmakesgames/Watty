#pragma once

#include "../renderable2d.h"
#include "fontmanager.h"

namespace letc { namespace graphics {

	class Label : public Renderable2D {
	public:
		Font* m_font;
		std::string text;
	public:
		//TODO we should remove x,y from all of these
		Label(std::string text, float x, float y, WattyColor color);
		Label(std::string text, WattyColor color);
		Label(std::string text, float x, float y, Font* font, WattyColor color);
		Label(std::string text, Font* font, WattyColor color);
		Label(std::string text, float x, float y, const std::string& fontName, WattyColor color);
		Label(std::string text, float x, float y, const std::string& fontName, unsigned int size, WattyColor color);
		Label(std::string text, const std::string& fontName, unsigned int size, WattyColor color);
		void submit(Renderer2D* renderer)const override;
	private:
		void validateFont(const std::string& name, int size = -1);

	};


}}