#include <graphics/layers/GUILayer.h>
namespace watty {namespace graphics {
	GUILayer::GUILayer(std::string name, graphics::Shader* shader): Layer(name ,new BatchRenderer2D(), shader){
		
	}
	
	void GUILayer::draw(){

	}

}}