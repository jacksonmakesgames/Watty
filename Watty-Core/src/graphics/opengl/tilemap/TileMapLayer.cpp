#include <graphics/tilemap/TileMap.h>
namespace watty {namespace graphics {
	TileMapLayer::TileMapLayer(float pixelMeterRatio, std::string name, unsigned int id, int tilesPerRow, int tilesPerColumn , float tileHeight, float tileWidth, std::vector<int> data, Texture* texture) :
		mName(name), mId(id), mTilesPerRow(tilesPerRow), mTilesPerColumn(tilesPerColumn), 
		mTileWidth(tileWidth),mTileHeight(tileHeight),mData(data), allTilesTexture(texture), 
		mWidth(tilesPerRow*tileWidth), mHeight(tilesPerColumn*tileHeight){
		//mData = std::vector<int>(data, data + sizeof(data) / sizeof(int));
		float x = -mWidth/2.0f;
		float y = mHeight / 2.0f;
		
		
		//x = 0;
		//y = 0;
		float xIndex = 0;
		for (size_t tileIndex = 0; tileIndex < data.size(); tileIndex++){
			if (xIndex >= mTilesPerRow) {
				//y -= 1.0f/mTilesPerRow;
				y -= mTileHeight;
				x = -mWidth/2;
				xIndex = 0;
			}
			//x = (tileIndex % mTilesPerRow);
			//y = (tileIndex / mTilesPerRow+1);
			int tileType = data[tileIndex];
			if (tileType != 0) {
				Tile* tile = new Tile(pixelMeterRatio, allTilesTexture, x, y, mTileWidth, mTileHeight, tileType);
				tile->setSize({ tileWidth, tileHeight });
				mTiles.push_back(tile);
			}
			
			x += mTileWidth;
			xIndex += 1;
		}
	}
	void TileMapLayer::submit(Renderer2D* renderer) const{
		renderer->push(glm::scale(glm::mat4(1.0f), glm::vec3(m_size.x, m_size.y, 0)));
		renderer->push(glm::translate(glm::mat4(1.0f), glm::vec3(getPosition().x, getPosition().y, 0)));
		for (size_t j = 0; j < mTiles.size(); j++)
		{
			mTiles[j]->submit(renderer);
		}
		renderer->pop();
		renderer->pop();
	}


	TileMapLayer::~TileMapLayer(){
		for (size_t i = 0; i < mTiles.size(); i++)
		{
			delete mTiles[i];
		}
	}
}}