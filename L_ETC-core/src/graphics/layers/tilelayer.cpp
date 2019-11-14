#include "tilelayer.h"
namespace letc {namespace graphics {
	TileLayer::TileLayer(Shader* shader) 
		: Layer(new BatchRenderer2D(), shader, math::Matrix4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f,-10.0f, 10.0f))
	{
	}

	TileLayer::~TileLayer() {
	}


}}