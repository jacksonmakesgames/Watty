#include <physics/PhysicsWorld2D.h>
namespace letc {namespace physics {
	DebugPhysics* PhysicsWorld2D::debugDraw = new DebugPhysics();
	b2World* PhysicsWorld2D::box2DWorld = new b2World(b2Vec2(0.0f, -20.0f)); // make gravity configurable

}}