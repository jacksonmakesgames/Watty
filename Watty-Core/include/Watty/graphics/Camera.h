#pragma once
#include "../graphics/layers/layer.h"

namespace letc { namespace graphics {
	enum class CameraMode
	{
		orthographic, perspective, custom
	};

	class Camera 
	{
	public:
		static std::vector<Camera*> allCameras;
		static Camera* sceneCamera;
	private:
		glm::mat4 m_projection;
		float m_size; // Half of the vertical view
		glm::vec3 m_position;
		glm::vec3 m_positionLastFrame;
		std::vector<Layer*>* m_layers;
		CameraMode m_mode;
		float m_clippingDepth;
		WattyColor mClearColor = Color::white;
		glm::vec2 windowSize = {1,1};

	public:
		glm::vec3& position;
		Camera(std::vector<Layer*>* layers, glm::vec3 position, float size, float clippingDepth, CameraMode mode, WattyColor clearColor = Color::white);
		inline void setSize(float newSize) { m_size = newSize;}
		inline float getSize() const {return m_size; }
		inline void setDepth(float newDepth) { m_clippingDepth = newDepth; }
		inline float getDepth() { return m_clippingDepth; }
		inline void setProjection(glm::mat4 newProjection) { m_projection = newProjection; m_mode = CameraMode::custom; }
		inline glm::vec2 getViewportSize() const { return m_size * windowSize; }
		inline glm::mat4 getProjection() { return m_projection; }
		inline WattyColor getClearColor() const { return mClearColor; }
		inline void setClearColor(WattyColor color) { mClearColor = color; }

		inline void setWindowSize(glm::vec2 size) { windowSize = size; };

		~Camera() {};

		void update();
		
	private:
		void init();


	private:

	};




} }