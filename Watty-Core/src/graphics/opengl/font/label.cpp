#include <graphics/font/label.h>
namespace watty {namespace graphics {
	Label::Label(LabelProperties props):Renderable2D(), properties(props) {
		setText(properties.text);
	}
	

	Label::Label(std::string text, Font* font, WattyColor color, OverflowMode overFlowMode):
	Renderable2D(){
		properties.font = font;
		properties.color = color;
		properties.overflowMode = overFlowMode;
		setText(text);
	}

	void Label::setText(std::string newText){
		properties.text = newText;
		handleOverflow();
	}

	
	void Label::submit(Renderer2D* renderer) const{
		renderer->drawString(properties.text, m_position, properties.font, properties.color, bounds);
	}


	void Label::handleOverflow(){
		int count = 0;
		switch (properties.overflowMode) {
		case OverflowMode::Expand:
			break;
		case OverflowMode::Wrap:
			for (size_t charI = 0; charI < properties.text.size(); charI++){
				count++;
				if (count > properties.charsPerLine) {
					count = 0;
					if(properties.text[charI-1] == ' ' || properties.text[charI] == ' ')
						properties.text.insert(charI, 1, '\n');
					else {
						properties.text.insert(charI, 1, '\n');
						properties.text.insert(charI, 1, '-');
					}
				}
			}
			break;
		default:
			return;
		}
	}


}}