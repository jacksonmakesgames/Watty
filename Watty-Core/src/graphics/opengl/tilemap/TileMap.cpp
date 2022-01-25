#include <graphics/tilemap/TileMap.h>
namespace watty {
namespace graphics {
	TileMap::TileMap(const char* pathToJsonMap, const char* pathToImage):mPathToMap(pathToJsonMap),mPathToImage(pathToImage){
		m_position = glm::vec2(.5f,-.5f);
		reloadMap();
	}

	const void TileMap::setPixelToMeterRatio(float newRatio){
		mPixelToMeterRatio = newRatio;
		mTileWidth /= mPixelToMeterRatio;
		mTileHeight /= mPixelToMeterRatio;
		reloadMap();
	}

	const void TileMap::reloadMap(){
		loadFromJson(mPathToMap, mPathToImage);

	}

	void TileMap::generatePhysicsFromLayer(json layer){
		std::vector<json> objects = layer["objects"].get<std::vector<json>>();
		for (size_t o = 0; o < objects.size(); o++){
			std::vector<json> polygon = objects[o]["polygon"].get<std::vector<json>>();
			float objX = objects[o]["x"].get<float>();
			float objY = objects[o]["y"].get<float>();
			std::vector<glm::vec2> shape = std::vector<glm::vec2>();
			for (size_t p = 0; p < polygon.size(); p++){
				shape.push_back(glm::vec2(objX + polygon[p]["x"].get<float>(), objY+polygon[p]["y"].get<float>()));
			}
			mPhysicsShapes.push_back(shape);
		}
	
	}


	void TileMap::buildPhysicsShapes() {
		watty::physics::MapBodyBuilder::buildShapes(mPhysicsShapes, mapSize.x, mapSize.y, mPixelToMeterRatio, physics::PhysicsWorld2D::box2DWorld);
	}
	

	// Load tiles from JSON, JSON map file should NOT have tileset embedded
	// image file should be in the same folder as tileset
	void TileMap::loadFromJson(const char* pathToMap, const char* pathToImage){
		std::vector<char> charsVec = read_file(pathToMap);
#ifndef WATTY_EMSCRIPTEN
		charsVec.resize(charsVec.size()/8); // TODO: not sure exactly why we need to divide by size of char here but not elsewhere works.. needs testing
#endif // !WATTY_EMSCRIPTEN

		if (charsVec.size() <= 0)
		{
			std::cout << "Error at JSON map file" << std::endl;
			return;
		}
		std::cout << std::endl;
		json parsedMap = json::parse(charsVec.begin(), charsVec.end());
		//json parsedSet = json::parse(read_file(pathToTileSet));
		
		mTilesPerRow = parsedMap["width"];
		mTilesPerColumn = parsedMap["height"];
		
		mTileWidth = parsedMap["tilewidth"].get<float>();
		mTileHeight = parsedMap["tileheight"].get<float>();

		mapSize = glm::vec2(mTilesPerRow * mTileWidth, mTilesPerColumn * mTileHeight);

		mTileWidth /= mPixelToMeterRatio;
		mTileHeight /= mPixelToMeterRatio;
		
		Texture* allTilesTexture = new Texture(pathToImage);
		mLayers.clear();
		if (parsedMap["layers"].is_array()) {
			std::vector<json> layers = parsedMap["layers"].get<std::vector<json>>();
			for (size_t lIndex = 0; lIndex < layers.size(); lIndex++) {
				if (layers.at(lIndex)["type"].get<std::string>() == "objectgroup") {
					generatePhysicsFromLayer(layers.at(lIndex));
				}
				else {
					mLayers.push_back(
						new TileMapLayer(
							mPixelToMeterRatio,
							layers.at(lIndex)["name"].get<std::string>(),
							layers.at(lIndex)["id"].get<int>(),
							layers.at(lIndex)["width"].get<int>(),
							layers.at(lIndex)["height"].get<int>(),
							mTileWidth,
							mTileHeight,
							layers.at(lIndex)["data"].get<std::vector<int>>(),
							allTilesTexture
						)
					);
				}
			}
		}
		else {
			//TODO LOG ERROR
		}
		
	}

}}