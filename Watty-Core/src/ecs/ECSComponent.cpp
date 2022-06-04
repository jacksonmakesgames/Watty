#include <Watty/ecs/ECSComponent.h>
namespace watty {
	/*
	std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>* BaseECSComponent::componentTypes;

	uint32_t BaseECSComponent::registerComponentType(ECSComponentCreateFunction createfn, ECSComponentFreeFunction freefn, size_t size) {
		if (componentTypes == nullptr) {
			componentTypes = new std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>();
		}
		
		uint32_t componentID = componentTypes->size();
		componentTypes->push_back(std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>(
			createfn, freefn, size)
		);
		return componentID;
	}
	*/



	std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t> >* BaseECSComponent::componentTypes;

	uint32_t BaseECSComponent::registerComponentType(ECSComponentCreateFunction createfn,
		ECSComponentFreeFunction freefn, size_t size)
	{
		if (componentTypes == nullptr) {
			componentTypes = new std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t> >();
		}
		uint32_t componentID = componentTypes->size();
		componentTypes->push_back(std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>(
			createfn, freefn, size));
		return componentID;
	}
}