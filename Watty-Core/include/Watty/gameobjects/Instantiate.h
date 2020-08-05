#pragma once
#include <gameobjects/GameObject.h>
#include <graphics/layers/layer.h>
#include <typeinfo>       // operator typeid
namespace letc {
	static class Instantiate {

	public:
		template <class type>
		static type* Create(glm::vec2 position, glm::vec2 size = {1,1},std::string layerName = "Default") {
			type* go = new type(position, size);
			if (layerName != "") {
				Layer* layer = Layer::getLayerByName(layerName);
				if (layer != nullptr)
					layer->add((GameObject*)go);
				else {
					//TODO log error
					std::cout << "Cannot add object of type: <" << typeid(type).name() << "> to layer: " << layerName << ", layer does not exist. Exiting" << std::endl;
					exit(1);
				}
			}
			return go;
		};

	};

	static void Destroy(GameObject* g) {
		//TODO no
		for (size_t i = 0; i < Layer::allLayers.size(); i++)
		{
			for (size_t j = 0; j < Layer::allLayers[i]->getGameObjects().size(); j++)
			{
				if (Layer::allLayers[i]->getGameObjects()[j] == g) {
					g->disable();
					Layer::allLayers[i]->remove(g);
				}

			}
		}
	}
}