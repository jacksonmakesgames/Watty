#include <physics/MapBodyBuilder.h>
namespace watty {namespace physics {
    MapBodyBuilder::MapBodyBuilder() {}

    std::vector<b2Body*> MapBodyBuilder::buildShapes(std::vector<std::vector<glm::vec2>> shapes,float width, float height, float pixelsPerTile, b2World* world)
    {
		std::vector<b2Body*> bodies = std::vector<b2Body*>();

		for (size_t s = 0; s < shapes.size(); s++) {
			b2BodyDef bd = b2BodyDef();
			bd.type = b2BodyType::b2_staticBody;
			//bd.position.Set(-map->getWidth()*.5f, map->getHeight()*.5f);
			b2Body* body = world->CreateBody(&bd);
			b2Vec2 verts[9999];
			b2Vec2* vertsPtr = verts;
			for (size_t v = 0; v < shapes[s].size(); v++)
			{
				*vertsPtr = b2Vec2(
					(shapes[s][v].x - width * .5f)/pixelsPerTile ,
					(height * .5f- shapes[s][v].y)/pixelsPerTile
				);
				vertsPtr++;
			}
			b2ChainShape* chain = new b2ChainShape();

			chain->CreateLoop(verts, shapes[s].size());

			b2FixtureDef def = b2FixtureDef();
			def.shape = chain;
			def.density = 1.0f;
			def.restitution = 0.0f;
			def.friction = 1.0f;
			def.restitution = 0.5;

			body->CreateFixture(&def);
			bodies.push_back(body);
		}

		return bodies;
    }

}}