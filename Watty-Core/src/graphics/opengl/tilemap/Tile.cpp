#include <graphics/tilemap/Tile.h>
namespace letc {namespace graphics {

	Tile::Tile(float pixelMeterRatio, Texture* texture,float x, float y, int width, int height, int offsetIndex):Sprite(x,y,1,1,texture){
		offsetIndex--;
		setPosition(glm::vec3(x,y,0));
		int totalWidth = texture->getNumColumns();
		int totalHeight = texture->getNumRows();
	/*	
		int rows =  totalWidth/ width;
		int cols =  totalHeight / height;

		int thisRow = offsetIndex / rows;
		int thisColumn = offsetIndex % rows;

		float uvAddW = ((float)width / (float)totalWidth);
		float uvAddH = ((float)height / (float)totalHeight);

		float zeroX = (float)(width * thisColumn) / totalWidth;
		float oneX = (float)(width * thisColumn) / totalWidth + uvAddW;

		float zeroY = 1 - ((float)(height * thisRow) / totalHeight);
		float oneY = 1 - (((float)(height * thisRow) / totalHeight) + uvAddH);*/

		const float tw = (float(width) / totalWidth)*pixelMeterRatio;
		const float th = (float(height) / totalHeight)*pixelMeterRatio;
		const int numPerRow = totalWidth / (width*pixelMeterRatio);
		const float tx = (offsetIndex % numPerRow) * tw;
		const float ty = (offsetIndex / numPerRow + 1) * th;

		//setUvs(
		//	glm::vec2(tx, ty), // se 
		//	glm::vec2(tx, ty+th), // nw
		//	glm::vec2(tx + tw, ty + th), // ne
		//	glm::vec2(tx+tw, ty)  // sw
		//);
		
		std::vector<glm::vec2> t = getUVs();

		//setUvs(
		//	glm::vec2(0.968750000, 0.0312500000), // se 
		//	glm::vec2(0.968750000, 0.0625000000), // ne
		//	glm::vec2(1, 0.0625000000), // nw
		//	glm::vec2(1, 0.0312500000)  // sw
		//);
		
		m_frameInfo.currentFrame = offsetIndex;
		m_frameInfo.rows = totalHeight / (height*pixelMeterRatio);
		m_frameInfo.cols = totalWidth / (width*pixelMeterRatio);

		//setUvs(
		//	glm::vec2(0, 0), // se 
		//	glm::vec2(0, 1), // ne
		//	glm::vec2(1, 1), // nw
		//	glm::vec2(1, 0)  // sw
		//);
	}

}}