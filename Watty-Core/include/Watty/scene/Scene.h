#pragma once
#include <string>
#include <vector>
#include <graphics/layers/layer.h>
#include <utils/file_utils.h>
#include <gameobjects/gameobject.h>

namespace watty {
	class Scene {
    
	public:
        std::vector<Layer*> m_layers;
        std::string name;
        std::string filepath;
        
        Scene(std::string path, std::string name);
        ~Scene();

        void load();
        void unload();
        void save();

	};

}