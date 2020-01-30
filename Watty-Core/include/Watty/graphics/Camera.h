#pragma once
//#include "../math/math.h"
#include "../graphics/layers/layer.h"
#include <vector>


namespace letc { namespace graphics {
	enum class CameraMode
	{
		orthographic, perspective, custom
	};

	class Camera 
	{
	public:
		static std::vector<Camera*> allCameras;
	private:
		glm::mat4 m_projection;
		glm::vec2 m_size;
		glm::vec3 m_position;
		glm::vec3 m_positionLastFrame;
		std::vector<Layer*>* m_layers;
		CameraMode m_mode;
		float m_clippingDepth;

	public:
		glm::vec3& position;
		Camera(std::vector<Layer*>* layers, glm::vec3 position, glm::vec2 size, float clippingDepth, CameraMode mode);
		inline void setSize(glm::vec2 newSize) { m_size = newSize; }
		inline glm::vec2 getSize() {return m_size; }
		inline void setProjection(glm::mat4 newProjection) { m_projection = newProjection; m_mode = CameraMode::custom; }
		~Camera();

		void update();
		
	private:
		void init();

	private:

	};




} }