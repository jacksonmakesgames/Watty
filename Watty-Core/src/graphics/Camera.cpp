#include <graphics/Camera.h>
#include <iostream>

namespace letc {namespace graphics {
	std::vector<Camera*> Camera::allCameras{};

	//TODO: right now we only support orthographic, we should add support for multiple projection modes
	Camera::Camera(std::vector<Layer*>* layers, math::Vector3 position, math::Vector2 size, float clippingDepth, CameraMode mode) :
		m_position(position), m_positionLastFrame(position), m_size(size),
		position(m_position),
		m_layers(layers),
		m_clippingDepth(clippingDepth),
		m_mode(mode)
	{
		if (mode == CameraMode::orthographic)
			m_projection = math::Matrix4::orthographic(position.x - size.x / 2.0f, position.x + size.x / 2.0f, position.y - size.y / 2.0f, position.y + size.y / 2.0f, position.z, m_clippingDepth);
		else
			m_projection = math::Matrix4::perspective(0, 0, 0, 0); // TODO this should be an error
		init();

	}

	void Camera::update(){
		//TODO, I bet we can change this to matrix translation rather than making a new matrix every frame
		if (m_mode == CameraMode::orthographic)
			m_projection = math::Matrix4::orthographic(m_position.x - m_size.x / 2.0f, m_position.x + m_size.x / 2.0f, m_position.y - m_size.y / 2.0f, m_position.y + m_size.y / 2.0f, 0.0f, m_clippingDepth);
		
		for (size_t i = 0; i < m_layers->size(); i++)
		{
			m_layers->at(i)->setProjection(m_projection);
		}

	}

	void Camera::init()
	{
		Camera::allCameras.push_back(this);

	}



}}
