#include <scene/scene.h>
namespace watty {
	
    Scene::Scene(std::string path, std::string name) {
        this->name = name;
        this->filepath = path;
        this->load();
    }
    
    Scene::~Scene() {
        this->unload();
    }

    void Scene::load() {
		std::vector<char> charsVec = read_file(filepath); // loads from resources
		// std::vector<char> charsVec = read_file_from_disk(filepath);
#ifndef WATTY_EMSCRIPTEN
		charsVec.resize(charsVec.size()/8); // TODO: not sure exactly why we need to divide by size of char here but not elsewhere works.. needs testing
#endif // !WATTY_EMSCRIPTEN

		if (charsVec.size() <= 0)
		{
			std::cout << "Error at scene file (json)" << std::endl;
			return;
		}
		std::cout << std::endl;
		json parsedJson = json::parse(charsVec.begin(), charsVec.end());
		//print parsedJson
        
        //json parsedSet = json::parse(read_file(pathToTileSet));
		auto layers_strings = parsedJson["layers"];
        std::cout << "PARSED:"<<std::endl;
        std::cout << layers_strings << std::endl;
        // print layer strings:
        // for (int i = 0; i < layers_strings.size(); i++) {
            // std::cout << layers_strings[i] << std::endl;
        // }
	}

    void Scene::unload() {
    }

    void Scene::save() {
        // print layers:
        json scene_json;
        for (int i = 0; i < m_layers.size(); i++) {
            std::cout << m_layers[i]->name << std::endl;
            json layer_json;
            layer_json["name"] = m_layers[i]->name;
            layer_json["hidden"] = m_layers[i]->hidden;
             
            for (int j = 0; j < m_layers[i]->getGameObjects().size(); j++) {
                // TODO need arbitrary way to save components
                GameObject* go = m_layers[i]->getGameObjects()[j];
                layer_json["gameobjects"][go->getUUID()]["name"] = go->name; 
                layer_json["gameobjects"][go->getUUID()]["enabled"] = go->isEnabled();
                layer_json["gameobjects"][go->getUUID()]["tag"] = go->getTag();
                layer_json["gameobjects"][go->getUUID()]["transform"]["position"]["x"] = go->transform->getPosition().x;
                layer_json["gameobjects"][go->getUUID()]["transform"]["position"]["y"] = go->transform->getPosition().y;
                 
            
            }

            layer_json["shader_frag"] = m_layers[i]->getShader()->getFragPath();
            layer_json["shader_vert"] = m_layers[i]->getShader()->getVertPath();
            layer_json["enabled"] = m_layers[i]->isEnabled();
            scene_json["layers"].push_back(layer_json);
        }
        std::string serialized_string = scene_json.dump(2);
        std::cout << serialized_string << std::endl;
        write_string_to_file(filepath, serialized_string);
    }
}
