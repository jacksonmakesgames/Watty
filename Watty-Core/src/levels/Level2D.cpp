#include <levels/Level2D.h>
namespace letc {
	Level2D::Level2D(){
	}


	Level2D::~Level2D(){
	}


	std::vector<const Layer*> Level2D::getLayers(){
		return mLayers;
	}


	void Level2D::addLayer(const Layer* layer){
		mLayers.push_back(layer);
	}


	Level2DProperties::Level2DProperties(std::string name): LevelProperties(){
		LevelProperties::name = name;
	}
}
