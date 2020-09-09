#include <graphics/layers/DebugPhysicsLayer.h>
namespace letc { namespace graphics {
	DebugPhysicsLayer::DebugPhysicsLayer(Camera& camera, Window& window) :
			mCamera(camera),
			m_debugRenderer(physics::DebugPhysics::instance->getRenderer()),
			Layer("Debug Physics Layer", physics::DebugPhysics::instance->getRenderer()),
			mWindow(window)

	{
		
		m_pixelToMeterRatio = glm::vec2(mWindow.getWidth(),mWindow.getHeight()) / camera.getSize();
		hidden = true; // Don't list in inspector	
		m_renderer = m_debugRenderer;
	}

	
	void DebugPhysicsLayer::draw(){
		if (!enabled_) return;
		physics::DebugPhysics::setProjection(getProjection());
		physics::PhysicsWorld2D::box2DWorld->DebugDraw(); //submit
	
	};


} }
