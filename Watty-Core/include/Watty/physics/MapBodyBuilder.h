#pragma once
#include <Box2D/Box2D.h>

#include <physics/PhysicsWorld2D.h>
namespace watty { namespace physics {
	
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
