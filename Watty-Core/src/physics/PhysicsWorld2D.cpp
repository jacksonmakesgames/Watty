#include <physics/PhysicsWorld2D.h>
namespace watty {namespace physics {
	DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
	b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, -20.0f)); // TODO make gravity configurable

}}