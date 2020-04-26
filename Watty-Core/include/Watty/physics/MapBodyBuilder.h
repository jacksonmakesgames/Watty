#pragma once
#include <box2d/box2d.h>

#include <physics/PhysicsWorld2D.h>
namespace letc { namespace physics {
	
	class MapBodyBuilder
	{
	public:
		static b2World* box2DWorld;
	private:
	public:
        MapBodyBuilder();
		static std::vector<b2Body*> buildShapes(std::vector<std::vector<glm::vec2>> shapes, float width, float height, float pixelsPerTile, b2World* world);

      
	private:
       
    
    
    };


} }
