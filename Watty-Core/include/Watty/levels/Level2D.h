#include <levels/level.h>
#include <graphics/layers/layer.h>

namespace letc {
	struct Level2DProperties : public LevelProperties {
		Level2DProperties(std::string name);
	};


	class Level2D : public Level {
	public:
	private:
		std::vector<const Layer*> mLayers;
	public:
		Level2D();
		~Level2D();
		std::vector<const Layer*> getLayers();
		void addLayer(const Layer* layer);


	};


}