#pragma once
#include <Watty/ecs/ECSComponent.h>

namespace letc {
	class BaseECSSystem {
	public:
		enum {
			FLAG_OPTIONAL = 1,
		};

		BaseECSSystem() {};
		virtual void updateComponents(float deltaTime, BaseECSComponent** components) {}
		const inline std::vector<uint32_t>& getComponentTypes() { return componentTypes; }
		const inline std::vector<uint32_t>& getComponentFlags() { return componentFlags; }

		bool isValid();

	protected:
		void addComponentType(uint32_t componentType, uint32_t componentFlag = 0);
	private:
		std::vector<uint32_t> componentTypes;
		std::vector<uint32_t> componentFlags;
	
	};

	class ECSSystemList {
	private:
		std::vector<BaseECSSystem*> systems;
	public:
		bool addSystem(BaseECSSystem& system);
		bool removeSystem(BaseECSSystem& system);
		inline size_t size() { return systems.size(); }
		inline BaseECSSystem* operator[](uint32_t index) { return systems[index]; }
	private:

	};
}