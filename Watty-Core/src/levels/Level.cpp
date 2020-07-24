#include <levels\Level.h>
namespace letc {
	Level::Level(){

	}


	Level::~Level(){
		for (size_t i = 0; i < mProperties.cameras.size(); i++){
			delete mProperties.cameras[i];
		}
	}

	void Level::addGameObject(const GameObject* gameObject){
		std::cout << "VIRTUAL METHOD ADD GAMEOBJECT (IN LEVEL) NOT IMPLEMENTED" << std::endl;
	}

	void Level::setName(std::string name){
		mProperties.name = name;
	}


	std::string Level::getName() const{
		mProperties.name;
	}


	std::vector<const graphics::Camera*> Level::getCameras(){
		return mProperties.cameras;
	}


	void Level::addCamera(const graphics::Camera* camera){
		mProperties.cameras.push_back(camera);
	}
}