#include <graphics/tilemap/TileMap.h>
namespace letc {namespace graphics {
	

	
	TileMap::TileMap(const char* pathToJsonMap, const char* pathToImage):mPathToMap(pathToJsonMap),mPathToImage(pathToImage){
		reloadMap();
	}

	const void TileMap::setPixelToMeterRatio(float newRatio){
		mPixelToMeterRatio = newRatio;
		mTileWidth /= mPixelToMeterRatio;
		mTileHeight /= mPixelToMeterRatio;
		mapSize /= mPixelToMeterRatio;
		reloadMap();
	}

	const void TileMap::reloadMap(){
		loadFromJson(mPathToMap, mPathToImage);

	}

	// Load tiles from JSON, JSON map file should NOT have tileset embedded
	// image file should be in the same folder as tileset
	void TileMap::loadFromJson(const char* pathToMap, const char* pathToImage){
		json parsedMap = json::parse(read_file(pathToMap));
		//json parsedSet = json::parse(read_file(pathToTileSet));
		
		mTilesPerRow = parsedMap["width"];
		mTilesPerColumn = parsedMap["height"];
		
		mTileWidth = parsedMap["tilewidth"].get<float>();
		mTileHeight = parsedMap["tileheight"].get<float>();

		mTileWidth /= mPixelToMeterRatio;
		mTileHeight /= mPixelToMeterRatio;
		mapSize = glm::vec2(mTilesPerRow*mTileWidth, mTilesPerColumn*mTileHeight);
		
		Texture* allTilesTexture = new Texture(pathToImage);
		mLayers.clear();
		if (parsedMap["layers"].is_array()) {
			std::vector<json> layers = parsedMap["layers"].get<std::vector<json>>();
			for (size_t lIndex = 0; lIndex < layers.size(); lIndex++) {
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
		else {
			//TODO LOG ERROR
		}
		
	}

}}