#pragma once

#include "../renderable2d.h"
#include "fontmanager.h"

namespace letc { namespace graphics {
	
	enum OverflowMode {
		Wrap, Expand
	};

	struct LabelProperties {
		std::string text;
		const Font* font;
		WattyColor color = Color::black;
		OverflowMode overflowMode = OverflowMode::Expand;
		int charsPerLine = 100;

	};

	class Label : public Renderable2D {
	public:
		LabelProperties properties;

	public:
		Label(LabelProperties properties);
		Label(std::string text, Font* font, WattyColor color, OverflowMode overFlowMode = OverflowMode::Expand);
		void setText(std::string newText);
		void submit(Renderer2D* renderer)const override;

	private:
		void handleOverflow();

	};


}}