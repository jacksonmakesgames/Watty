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

		void submit(Renderer2D* renderer)const override;

		inline const std::vector<Tile*> getTiles() { return mTiles; }

		~TileMapLayer();



	};
}}