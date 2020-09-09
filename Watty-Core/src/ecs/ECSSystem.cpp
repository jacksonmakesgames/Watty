#include <Watty/ecs/ECSSystem.h>
namespace letc {
	/*
	bool BaseECSSystem::isValid()
	{
		for (uint32_t i = 0; i < componentFlags.size(); i++){
			if ((componentFlags[i] & BaseECSSystem::FLAG_OPTIONAL) == 0) {
				return true;
			}
		}
		return false;
	}


	void BaseECSSystem::addComponentType(uint32_t componentType, uint32_t componentFlag){
		componentFlags.push_back(componentFlag);
		componentTypes.push_back(componentType);
	}


	bool ECSSystemList::addSystem(BaseECSSystem& system)
	{
		if (!system.isValid())
			return false;
		systems.push_back(&system);
		return true;
	}

	bool ECSSystemList::removeSystem(BaseECSSystem& system) {
		for (uint32_t i = 0; i < systems.size(); i++) {
			if (&system == systems[i]) {
				systems.erase(systems.begin() + i);
				return true;
			}
		}
		return false;
	}

	*/


	bool BaseECSSystem::isValid()
	{
		for (uint32_t i = 0; i < componentFlags.size(); i++) {
			if ((componentFlags[i] & BaseECSSystem::FLAG_OPTIONAL) == 0) {
				return true;
			}
		}
		return false;
	}

	bool ECSSystemList::removeSystem(BaseECSSystem& system)
	{
		for (uint32_t i = 0; i < systems.size(); i++) {
			if (&system == systems[i]) {
				systems.erase(systems.begin() + i);
				return true;
			}
		}
		return false;
	}

}