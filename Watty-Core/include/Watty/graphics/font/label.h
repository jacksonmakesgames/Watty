#pragma once

#include "../renderable2d.h"
#include "fontmanager.h"

namespace watty { namespace graphics {
	
	enum OverflowMode {
		Wrap, Expand
	};

	struct LabelProperties {
		OverflowMode overflowMode = OverflowMode::Expand;
		int charsPerLine = 100;
		const Font* font;
		std::string text;
		WattyColor color = Color::black;

	};

	class Label : public Renderable2D {
	public:
		LabelProperties properties;
	private:
	public:
		Label(LabelProperties properties);
		Label(std::string text, Font* font, WattyColor color, OverflowMode overFlowMode = OverflowMode::Expand);
		void setText(std::string newText);
		void submit(Renderer2D* renderer)const override;

	private:
		void handleOverflow();

	};


}}