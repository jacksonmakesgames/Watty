#pragma once
#include "renderer2d.h"
namespace letc { namespace graphics {
	class SimpleRenderer2D : public Renderer2D {
	private:
	public:
		SimpleRenderer2D();
		void submit(const Renderable2D* renderable) override {};
		void begin() override {};
		void submit(const Renderable2D* renderable) override {};
		void end() override {};
		void flush() override {};
		~SimpleRenderer2D();


	};


} }