#include "GridLayer.h"
namespace letc { namespace graphics {
	GridLayer::GridLayer(graphics::Shader* shader, float left, float right, float bottom, float top, float near, float far) : Layer("Grid Layer",new GridRenderer(left, right, bottom, top, near,far), shader, math::Matrix4::orthographic(left, right, bottom, top, near,far)) {
	
	}

} }
