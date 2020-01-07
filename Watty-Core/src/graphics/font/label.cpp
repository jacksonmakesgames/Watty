#include "label.h"

namespace letc {namespace graphics {
	Label::Label(std::string text, float x, float y, unsigned int color) :
		Renderable2D(), text(text){
		m_position = math::Vector3(x, y, 0);
		m_color = color;
		m_font = FontManager::get("default");
		m_texture = m_font->getTexture();

	}
	Label::Label(std::string text, unsigned int color) :
		Renderable2D(), text(text){
		m_position = math::Vector3(0, 0, 0);
		m_color = color;
		m_font = FontManager::get("default");
		m_texture = m_font->getTexture();

	}
	Label::Label(std::string text, float x, float y, Font* font, unsigned int color):
	Renderable2D(), text(text){
		m_position = math::Vector3(x, y, 0);
		m_color = color;
		m_font = font;
		m_texture = m_font->getTexture();

	}
	Label::Label(std::string text, Font* font, unsigned int color):
	Renderable2D(), text(text){
		m_position = math::Vector3(0, 0, 0);
		m_color = color;
		m_font = font;
		m_texture = m_font->getTexture();

	}

	Label::Label(std::string text, float x, float y, const std::string& fontName, unsigned int color)
		:Renderable2D(), text(text){
		m_position = math::Vector3(x, y, 0);
		m_color = color;
		m_font = FontManager::get(fontName);
		m_texture = m_font->getTexture();
		validateFont(fontName);
	}

	Label::Label(std::string text, float x, float y, const std::string& fontName, unsigned int size, unsigned int color):
	Renderable2D(), text(text) {
		m_position = math::Vector3(x, y, 0);
		m_color = color;
		m_font = FontManager::get(fontName, size);
		m_texture = m_font->getTexture();

		validateFont(fontName, size);
	}
	Label::Label(std::string text, const std::string& fontName, unsigned int size, unsigned int color) :
		Renderable2D(), text(text) {
		
		m_position = math::Vector3(0, 0, 0);
		m_color = color;
		m_font = FontManager::get(fontName, size);
		if (m_font == nullptr) {
			std::cout << "Error, no font found for label" << std::endl;
			return;
		}
		m_texture = m_font->getTexture();

		validateFont(fontName, size);
	}

	void Label::submit(Renderer2D* renderer) const{
		renderer->drawString(text, m_position, *m_font, m_color);
	}

	void Label::validateFont(const std::string& name, int size){
		if (m_font != nullptr) return;
		// TODO: log error

		std::cout << "-ERROR- NULL font: " << name;
		if (size > 0)
			std::cout << " Size: " << size;
		std::cout << std::endl;
		
		// use default font
		m_font = FontManager::get("default");
		m_texture = m_font->getTexture();

	}


}}