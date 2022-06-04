#pragma once
#include <cstdint>
#include <vector>
#include <tuple>

#define NULL_COPY_AND_ASSIGN(T) \
	T(const T& other) {(void)other;} \
	void operator=(const T& other) { (void)other; }

namespace watty {
	/*
	struct BaseECSComponent;
	typedef void* EntityHandle;
	typedef uint32_t (*ECSComponentCreateFunction)(std::vector<uint8_t>& memory, EntityHandle entity, BaseECSComponent* comp);
	typedef void (*ECSComponentFreeFunction)(BaseECSComponent* comp);

	#define NULL_ENTITY nullptr
	struct BaseECSComponent {
	public:
		static uint32_t registerComponentType(ECSComponentCreateFunction createfn, ECSComponentFreeFunction freefn, size_t size);
		EntityHandle entity = NULL_ENTITY;

		// Getters:
		inline static ECSComponentCreateFunction getTypeCreateFunction(uint32_t id) { return std::get<0>((*componentTypes)[id]); }
		inline static ECSComponentFreeFunction getTypeFreeFunction(uint32_t id) { return std::get<1>((*componentTypes)[id]); }
		inline static size_t getTypeSize(uint32_t id) { return std::get<2>((*componentTypes)[id]); }

		inline static bool isTypeValid(uint32_t id) {
			return id < componentTypes->size();
		}
	private:
		static std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t>>* componentTypes;

	};

	template<typename T>
	struct ECSComponent : public BaseECSComponent {
		static const ECSComponentCreateFunction CREATE_FUNCTION;
		static const ECSComponentFreeFunction   FREE_FUNCTION;
		static const uint32_t ID;
		static const size_t SIZE;
	};

	template<typename Component>
	uint32_t ECSComponentCreate(std::vector<uint8_t>& memory, EntityHandle entity, BaseECSComponent* comp) {
		uint32_t index = memory.size();
		memory.resize(index+Component::SIZE);
		Component* component = new(&memory[index]) Component(*(Component*)comp);
		component->entity = entity;
		return index;

	}

	template<typename Component>
	void ECSComponentFree(BaseECSComponent* comp) {
		Component* component = (Component*)comp;
		component->~Component();
	}


	template<typename T>
	const uint32_t ECSComponent<T>::ID(BaseECSComponent::registerComponentType(ECSComponentCreate<T>, ECSComponentFree<T>, sizeof(T)));
	
	template<typename T>
	const size_t ECSComponent<T>::SIZE(sizeof(T));
	
	template<typename T>
	const ECSComponentCreateFunction ECSComponent<T>::CREATE_FUNCTION(ECSComponentCreate<T>);
	template<typename T>
	const ECSComponentFreeFunction ECSComponent<T>::FREE_FUNCTION(ECSComponentFree<T>);


	*/

	struct BaseECSComponent;
	typedef void* EntityHandle;
	typedef uint32_t(*ECSComponentCreateFunction)(std::vector<uint8_t>& memory, EntityHandle entity, BaseECSComponent* comp);
	typedef void (*ECSComponentFreeFunction)(BaseECSComponent* comp);
#define NULL_ENTITY nullptr

	struct BaseECSComponent
	{
	public:
		static uint32_t registerComponentType(ECSComponentCreateFunction createfn,
			ECSComponentFreeFunction freefn, size_t size);
		EntityHandle entity = NULL_ENTITY;

		inline static ECSComponentCreateFunction getTypeCreateFunction(uint32_t id)
		{
			return std::get<0>((*componentTypes)[id]);
		}

		inline static ECSComponentFreeFunction getTypeFreeFunction(uint32_t id)
		{
			return std::get<1>((*componentTypes)[id]);
		}

		inline static size_t getTypeSize(uint32_t id)
		{
			return std::get<2>((*componentTypes)[id]);
		}

		inline static bool isTypeValid(uint32_t id)
		{
			return id < componentTypes->size();
		}
	private:
		static std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, size_t> >* componentTypes;
	};

	template<typename T>
	struct ECSComponent : public BaseECSComponent
	{
		static const ECSComponentCreateFunction CREATE_FUNCTION;
		static const ECSComponentFreeFunction FREE_FUNCTION;
		static const uint32_t ID;
		static const size_t SIZE;
	};

	template<typename Component>
	uint32_t ECSComponentCreate(std::vector<uint8_t>& memory, EntityHandle entity, BaseECSComponent* comp)
	{
		uint32_t index = memory.size();
		memory.resize(index + Component::SIZE);
		Component* component = new(&memory[index])Component(*(Component*)comp);
		component->entity = entity;
		return index;
	}

	template<typename Component>
	void ECSComponentFree(BaseECSComponent* comp)
	{
		Component* component = (Component*)comp;
		component->~Component();
	}

	template<typename T>
	const uint32_t ECSComponent<T>::ID(BaseECSComponent::registerComponentType(ECSComponentCreate<T>, ECSComponentFree<T>, sizeof(T)));

	template<typename T>
	const size_t ECSComponent<T>::SIZE(sizeof(T));

	template<typename T>
	const ECSComponentCreateFunction ECSComponent<T>::CREATE_FUNCTION(ECSComponentCreate<T>);

	template<typename T>
	const ECSComponentFreeFunction ECSComponent<T>::FREE_FUNCTION(ECSComponentFree<T>);


}