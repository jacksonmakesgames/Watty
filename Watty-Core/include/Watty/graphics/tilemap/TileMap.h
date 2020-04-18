#pragma once
#include "Tile.h"
#include "TileMapLayer.h"
#include <utils/file_utils.h>


namespace letc {namespace graphics {
	class TileMap : public Renderable2D {
	public:
		glm::vec2 mapSize = glm::vec2();
	private:
		float mPixelToMeterRatio = 1;
		std::vector<TileMapLayer*> mLayers;
		void loadFromJson(const char* pathToMap, const char* pathToImage);
		int mTilesPerRow;
		int mTilesPerColumn;
		float mTileHeight;
		float mTileWidth;
		const char* mPathToMap;
		const char* mPathToImage;


	public:
		TileMap(const char* pathToJsonMap, const char* pathToImage);
		const void setPixelToMeterRatio(float newRatio);
		const void reloadMap();

		inline const int getNumColumns() { return mTilesPerRow; }
		inline const int getNumRows() { return mTilesPerColumn; }
		inline const int getWidth() { return mapSize.x; }
		inline const int getHeight() { return mapSize.y; }
		inline std::vector<TileMapLayer*> getLayers() { return mLayers; }
		
		void submit(Renderer2D* renderer)const override{
			renderer->push(glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0)));
			renderer->push(glm::translate(glm::mat4(1.0f), glm::vec3(getPosition().x, getPosition().y, 0)));
			for (size_t i = 0; i < mLayers.size(); i++){
				mLayers[i]->submit(renderer);
			}
			renderer->pop();
			renderer->pop();

		}
		
		~TileMap() {
			for (size_t i = 0; i < mLayers.size(); i++)
			{
				delete mLayers[i];
			}
		};

	};
}}