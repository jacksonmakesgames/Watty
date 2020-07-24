#include <graphics/Camera.h>
#include <gameobjects/GameObject.h>

namespace letc {
	
	struct LevelProperties {
		std::string name = "Level";
		std::vector<const graphics::Camera*> cameras;

	};

	class Level {

	public:

	private:
		LevelProperties mProperties;
		std::string mName;
	public:
		Level();
		~Level();
		
		//virtual void addGameObject();
		virtual void addGameObject(const GameObject* gameObject);


		void setName(std::string name);
		std::string getName() const;

		std::vector<const graphics::Camera*> getCameras();
		void addCamera(const graphics::Camera* camera);

	private:


	};



}