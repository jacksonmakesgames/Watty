#include <Watty/ecs/ECS.h>
namespace letc {
	ECS::~ECS(){
		// Free Entity Memory
		for (uint32_t i = 0; i < entities.size(); i++){
			delete entities[i];
		}

		// Free component memory
		for (std::map<uint32_t, std::vector<uint8_t>>::iterator it = components.begin(); it != components.end(); ++it) {
			size_t typeSize = BaseECSComponent::getTypeSize(it->first);
			ECSComponentFreeFunction freefn = BaseECSComponent::getTypeFreeFunction(it->first);
			for (uint32_t i = 0; i < it->second.size(); i+=typeSize){
				freefn((BaseECSComponent*)&it->second[i]);
			}
		}
	}

	EntityHandle ECS::makeEntity(BaseECSComponent** entityComponents, const uint32_t* componentIDs, size_t numComponents){
		std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>* newEntity = new std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>();
		EntityHandle handle = (EntityHandle)newEntity;

		for (uint32_t i = 0; i < numComponents; i++){
			//Check componentID is valid
			if (!BaseECSComponent::isTypeValid(componentIDs[i])) {
				printf("ERROR: %u is not a valid type, not adding entity", componentIDs[i]);
				delete newEntity;
				return NULL_ENTITY;
			}
			// Create component
			addComponentInternal(handle, newEntity->second, componentIDs[i], entityComponents[i]);

		}

		newEntity->first = entities.size(); // Index
		entities.push_back(newEntity);
		return handle;

	}

	void ECS::removeEntity(EntityHandle handle){
		std::vector<std::pair<uint32_t, uint32_t>>& entity = handleToEntity(handle);

		// will be constant time in practice because there will not be that many entities
		for (uint32_t i = 0; i < entity.size(); i++){
			deleteComponent(entity[i].first, entity[i].second );
		}

		// Move the last entity in the list to the location of the deleted entity (order of entity list does not matter)
		uint32_t destIndex = handleToEntityIndex(handle);
		uint32_t srcIndex = entities.size() - 1;
		delete entities[destIndex];
		entities[destIndex] = entities[srcIndex];
		entities[destIndex]->first = destIndex;
		entities.pop_back();

	}


	void ECS::updateSystems(ECSSystemList& systemList, float deltaTime){
		std::vector<BaseECSComponent*> componentParam;
		std::vector<std::vector<uint8_t>*> componentArrays;
		for (uint32_t i = 0; i < systemList.size(); i++){
			const std::vector<uint32_t>& componentTypes = systemList[i]->getComponentTypes();
			if (componentTypes.size() == 1) {
				size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[0]);
				std::vector<uint8_t>& componentsArray = components[componentTypes[0]];
				for (uint32_t j = 0; j < componentsArray.size(); j+=typeSize){
					BaseECSComponent* comp = (BaseECSComponent*)&componentsArray[j];
					systemList[i]->updateComponents(deltaTime, &comp);
				}
			}
			else {
				updateSystemWithMultipleComponents(i, systemList, deltaTime, componentTypes, componentParam, componentArrays);
			}
		}
	}

	void ECS::deleteComponent(uint32_t componentID, uint32_t index){
		std::vector<uint8_t> componentArray = components[componentID];

		ECSComponentFreeFunction freefn = BaseECSComponent::getTypeFreeFunction(componentID);
		size_t typeSize = BaseECSComponent::getTypeSize(componentID);
		uint32_t srcIndex = componentArray.size() - typeSize;

		BaseECSComponent* destComponent = (BaseECSComponent*)&componentArray[index];
		BaseECSComponent* srcComponent = (BaseECSComponent*)&componentArray[srcIndex];

		freefn(destComponent);

		// Order does matter!
		if (index == srcIndex) {
			componentArray.resize(srcIndex);
			return;
		}

		memcpy(destComponent, srcComponent,typeSize);
		
		std::vector<std::pair<uint32_t, uint32_t>>& srcComponents = handleToEntity(srcComponent->entity);
		for (uint32_t i = 0; i < srcComponents.size(); i++){
			// first is type, second is index
			if (componentID == srcComponents[i].first && srcIndex == srcComponents[i].second) {
				srcComponents[i].second = index;
				break;
			}
		}
		componentArray.resize(srcIndex);
	}

	bool ECS::removeComponentInternal(EntityHandle handle, uint32_t componentID)
	{
		std::vector<std::pair<uint32_t, uint32_t>>& entityComponents = handleToEntity(handle);
		for (uint32_t i = 0; i < entityComponents.size(); i++) {
			// first is type, second is index
			if (componentID == entityComponents[i].first) {
				deleteComponent(entityComponents[i].first, entityComponents[i].second);
				uint32_t srcIndex = entityComponents.size() - 1;
				uint32_t destIndex = i;
				entityComponents[destIndex] = entityComponents[srcIndex];
				entityComponents.pop_back();
				return true;
			}
		}
		return false;
	}

	void ECS::addComponentInternal(EntityHandle handle, std::vector<std::pair<uint32_t, uint32_t>>& entity, uint32_t componentID, BaseECSComponent* component){
		ECSComponentCreateFunction createfn = BaseECSComponent::getTypeCreateFunction(componentID);
		std::pair newPair = std::pair<uint32_t, uint32_t>();
		newPair.first = componentID;
		newPair.second = createfn(components[componentID], handle, component);
		entity.push_back(newPair);
	}

	BaseECSComponent* ECS::getComponentInternal(std::vector<std::pair<uint32_t, uint32_t>>& entityComponents, std::vector<uint8_t>& componentsArray,uint32_t componentID){
		for (uint32_t i = 0; i < entityComponents.size(); i++) {
			// first is type, second is index
			if (componentID == entityComponents[i].first) {
				return (BaseECSComponent*)&componentsArray[entityComponents[i].second];
			}
		}
		return nullptr;
	}
	
	// not cache perfect, could be improved TODO
	void ECS::updateSystemWithMultipleComponents(uint32_t index, ECSSystemList& systemList, float deltaTime,
		const std::vector<uint32_t>& componentTypes, std::vector<BaseECSComponent*>& componentParam,
		std::vector<std::vector<uint8_t>*>& componentArrays)
	{
		const std::vector<uint32_t>& componentFlags = systemList[index]->getComponentFlags();


		componentParam.resize(std::max(componentParam.size(), componentTypes.size()));
		componentArrays.resize(std::max(componentArrays.size(), componentTypes.size()));
		for (uint32_t i = 0; i < componentTypes.size(); i++){
			componentArrays[i] = &components[componentTypes[i]];
		}


		uint32_t minSizeIndex = findLeastCommonComponent(componentTypes, componentFlags);
		size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[minSizeIndex]);
		std::vector<uint8_t>& array = *componentArrays[minSizeIndex];
		for (uint32_t i = 0; i < array.size(); i += typeSize) {
			componentParam[minSizeIndex] = (BaseECSComponent*)&array[i];
			std::vector<std::pair<uint32_t, uint32_t>>& entityComponents
				= handleToEntity(componentParam[minSizeIndex]->entity); // TODO double dereference
			bool isValid = true;

			for (uint32_t j = 0; j < componentTypes.size(); j++){
				if (j == minSizeIndex)
					continue;

				componentParam[j] = getComponentInternal(entityComponents, *componentArrays[j], componentTypes[j]);
				// Doesn't exist and is not optional
				if (componentParam[j] == nullptr && ((componentFlags[j]&BaseECSSystem::FLAG_OPTIONAL) == 0)) {
					isValid = false;
					break;
				}
			}
			if (isValid) {
				systemList[i]->updateComponents(deltaTime, &componentParam[0]);
			}
		}
	}

	uint32_t ECS::findLeastCommonComponent(const std::vector<uint32_t>& componentTypes, const std::vector<uint32_t>& componentFlags){
		uint32_t minSize  = (uint32_t) -1;
		uint32_t minIndex = (uint32_t) -1;
		for (uint32_t i = 0; i < componentTypes.size(); i++){
			if ((componentFlags[i] & BaseECSSystem::FLAG_OPTIONAL) != 0) {
				continue;
			}
			size_t typeSize = BaseECSComponent::getTypeSize(componentTypes[i]);
			uint32_t size = components[componentTypes[i]].size() / typeSize;
			if (size <= minSize) {
				minSize = size;
				minIndex = i;
			}
		}
		return minIndex;
	}
}