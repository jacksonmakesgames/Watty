#pragma once
#include <Watty/ecs/ECSComponent.h>

namespace watty {

	/*
	class BaseECSSystem {
	public:
		enum {
			FLAG_OPTIONAL = 1,
		};

		BaseECSSystem() {};
		virtual void updateComponents(float deltaTime, BaseECSComponent** components) {}
		const inline std::vector<uint32_t>& getComponentTypes() { 
			return componentTypes; }
		const inline std::vector<uint32_t>& getComponentFlags() { return componentFlags; }

		bool isValid();

	protected:
		void addComponentType(uint32_t componentType, uint32_t componentFlag = 0);
	private:
		std::vector<uint32_t> componentTypes = std::vector<uint32_t>();
		std::vector<uint32_t> componentFlags = std::vector<uint32_t>();
	
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
	*/


	class BaseECSSystem
	{
	public:
		enum
		{
			FLAG_OPTIONAL = 1,
		};
		BaseECSSystem() {}
		virtual void updateComponents(float delta, BaseECSComponent** components) {}
		const std::vector<uint32_t>& getComponentTypes()
		{
			return componentTypes;
		}
		const std::vector<uint32_t>& getComponentFlags()
		{
			return componentFlags;
		}
		bool isValid();
	protected:
		void addComponentType(uint32_t componentType, uint32_t componentFlag = 0)
		{
			componentTypes.push_back(componentType);
			componentFlags.push_back(componentFlag);
		}
	private:
		std::vector<uint32_t> componentTypes;
		std::vector<uint32_t> componentFlags;
	};

	class ECSSystemList
	{
	public:
		inline bool addSystem(BaseECSSystem& system)
		{
			if (!system.isValid()) {
				return false;
			}
			systems.push_back(&system);
			return true;
		}
		inline size_t size() {
			return systems.size();
		}
		inline BaseECSSystem* operator[](uint32_t index) {
			return systems[index];
		}
		bool removeSystem(BaseECSSystem& system);
	private:
		std::vector<BaseECSSystem*> systems;
	};

}