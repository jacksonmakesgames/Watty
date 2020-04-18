#pragma once
#include "Tile.h"
#include <vector>

namespace letc {namespace graphics {
	class TileMapLayer: public Renderable2D{
	private:
		int mTilesPerRow, mTilesPerColumn;
		float mTileWidth, mTileHeight;
		float mWidth, mHeight;
		std::vector<Tile*> mTiles;
		std::string mName;
		std::vector<int> mData;
		unsigned int mId;
		Texture* allTilesTexture;

	public:
		TileMapLayer(float pixelMeterRatio, std::string name, unsigned int id, int tilesPerRow, int tilesPerColumn, float tileHeight, float tileWidth, std::vector<int> data, Texture* texture);

		void submit(Renderer2D* renderer)const override {
			renderer->push(glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 0)));
			renderer->push(glm::translate(glm::mat4(1.0f), glm::vec3(getPosition().x, getPosition().y, 0)));
			for (size_t j = 0; j < mTiles.size(); j++)
			{
				mTiles[j]->submit(renderer);
			}
			renderer->pop();
			renderer->pop();

		}


		inline const std::vector<Tile*> getTiles() { return mTiles; }

		~TileMapLayer() {
			for (size_t i = 0; i < mTiles.size(); i++)
			{
				delete mTiles[i];
			}
		};



	};
}}