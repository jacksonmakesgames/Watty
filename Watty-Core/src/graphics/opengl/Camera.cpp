#include <graphics/Camera.h>

namespace watty {namespace graphics {
	std::vector<Camera*> Camera::allCameras{};
	Camera* Camera::sceneCamera = nullptr;
	//TODO: right now we only support orthographic, we should add support for multiple projection modes
	Camera::Camera(std::vector<Layer*>* layers, glm::vec3 position, float size, float clippingDepth, CameraMode mode, WattyColor clearCol) :
		m_position(position), m_positionLastFrame(position), m_size(size),
		position(m_position),
		m_layers(layers),
		m_clippingDepth(clippingDepth),
		m_mode(mode),
		mClearColor(clearCol)
	{

		glm::vec2 viewportSize = windowSize * m_size;

		if (mode == CameraMode::orthographic)
			m_projection = glm::ortho(
				position.x - viewportSize.x / 2.0f,
				position.x + viewportSize.x / 2.0f,
				position.y - viewportSize.y / 2.0f, position.y + viewportSize.y / 2.0f,
				position.z, m_clippingDepth);
		else
			m_projection = glm::perspective(0, 0, 0, 0); // TODO this should be an error
		init();

	}

	void Camera::update(){
		//TODO, I bet we can change this to matrix translation rather than making a new matrix every frame
		//if (m_mode == CameraMode::orthographic)
		glm::vec2 size = windowSize * m_size;

			m_projection = glm::ortho(
				m_position.x - size.x / 2.0f,
				m_position.x + size.x / 2.0f,
				m_position.y - size.y / 2.0f,
				m_position.y + size.y / 2.0f,
				0.0f, m_clippingDepth);
		
		for (size_t i = 0; i < m_layers->size(); i++)
		{
			m_layers->at(i)->setProjection(m_projection);
		}

	}

	void Camera::init()
	{
		if (Camera::allCameras.size() == 0) 
			Camera::sceneCamera = this;

		Camera::allCameras.push_back(this);
	}




}}
