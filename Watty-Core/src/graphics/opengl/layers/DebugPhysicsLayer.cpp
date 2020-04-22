#include <graphics/layers/DebugPhysicsLayer.h>
namespace letc { namespace graphics {
	DebugPhysicsLayer::DebugPhysicsLayer(Camera& camera, Window& window) :
			mCamera(camera),
			m_debugRenderer(physics::DebugPhysics::instance->getRenderer()),
			Layer("Debug Physics Layer",m_debugRenderer),
			mWindow(window)

	{
		m_pixelToMeterRatio = glm::vec2(mWindow.getWidth(),mWindow.getHeight()) / camera.getSize();


	}

	
	void DebugPhysicsLayer::draw(){
		if (!enabled) return;
		physics::DebugPhysics::setProjection(getProjection());
		physics::PhysicsWorld2D::box2DWorld->DrawDebugData(); //submit
	
	};


} }
