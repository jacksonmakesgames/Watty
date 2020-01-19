#pragma once
#include "../math/math.h"
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
		math::Matrix4 m_projection;
		math::Vector2 m_size;
		math::Vector3 m_position;
		math::Vector3 m_positionLastFrame;
		std::vector<Layer*>* m_layers;
		CameraMode m_mode;
		float m_clippingDepth;

	public:
		math::Vector3& position;
		Camera(std::vector<Layer*>* layers, math::Vector3 position, math::Vector2 size, float clippingDepth, CameraMode mode);
		inline void setSize(math::Vector2 newSize) { m_size = newSize; }
		inline void setProjection(math::Matrix4 newProjection) { m_projection = newProjection; m_mode = CameraMode::custom; }
		~Camera();

		void update();
		
	private:
		void init();

	private:

	};




} }