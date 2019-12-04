#include "GUILayer.h"
namespace letc {namespace graphics {
	GUILayer::GUILayer(std::string name, graphics::Shader* shader, math::Matrix4 prMatrix): Layer(name ,new BatchRenderer2D(), shader, prMatrix){
		
	}
	
	void GUILayer::draw(){

	}

}}