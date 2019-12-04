#pragma once
#include "../../ext/Box2D/Box2D.h"
#include <iostream>
#include <vector>
#include "../GameObject.h"

namespace letc { namespace physics {

	class QueryAABBCallback : public b2QueryCallback
	{
	public:
		bool hit = false;
		std::vector<b2Fixture*> fixtures;
		std::vector<GameObject*> gameObjects;
	private:
		Layer* m_testLayer;
	public:
		QueryAABBCallback(Layer* testLayer): m_testLayer(testLayer) {
		}

		bool ReportFixture(b2Fixture* fixture) override {
			hit = true;

			for (size_t i = 0; i < m_testLayer->getGameObjects().size(); i++)
			{
				// TODO: we could make this sort gameObjects by distance from the center, etc
				if (m_testLayer->getGameObjects()[i]->hasFixture(fixture))
					gameObjects.push_back(m_testLayer->getGameObjects()[i]);
			}

			fixtures.push_back(fixture);
			return true;
		
		}

	private:

	};




} }