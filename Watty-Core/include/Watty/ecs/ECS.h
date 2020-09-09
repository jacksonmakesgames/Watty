#pragma once
#include <Watty/ecs/ECSComponent.h>
#include <Watty/ecs/ECSSystem.h>

#include <map>
#include <algorithm>    // std::max



namespace letc {
	/*
	class ECS {
	public:
		ECS(){}

		~ECS();

		//Entities:
		EntityHandle makeEntity(BaseECSComponent** components, const uint32_t* componentIDs, size_t numComponents);
		// see templates below	

		void removeEntity(EntityHandle handle);
		

		//Components:
		template <class Component>
		void addComponent(EntityHandle entity, Component* component);
		
		template <class Component>
		bool removeComponent(EntityHandle entity);

		template <class Component>
		Component* getComponent(EntityHandle entity);


		//Systems:
		void updateSystems(ECSSystemList& systemList, float deltaTime);

	private:
		std::map<uint32_t, std::vector<uint8_t>> components;
		std::vector<std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>*> entities;

		inline std::pair< uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>* handleToRawType(EntityHandle handle) {
			return (std::pair < uint32_t, std::vector<std::pair<uint32_t, uint32_t>>>*) handle;
		}

		inline uint32_t handleToEntityIndex(EntityHandle handle) {
			return handleToRawType(handle)->first;
		}

		inline std::vector<std::pair<uint32_t, uint32_t>>& handleToEntity(EntityHandle handle) {
			return handleToRawType(handle)->second;
		}

		void deleteComponent(uint32_t id, uint32_t index);
		bool removeComponentInternal(EntityHandle handle,uint32_t componentID);
		void addComponentInternal(EntityHandle handle, std::vector<std::pair<uint32_t, uint32_t>>& entity, uint32_t componentID,  BaseECSComponent* component );
		BaseECSComponent* getComponentInternal(std::vector<std::pair<uint32_t, uint32_t>>& entityComponents, std::vector<uint8_t>& componentsArray, uint32_t componentID);

		void updateSystemWithMultipleComponents(uint32_t index, ECSSystemList& systemList, float deltaTime,
			const std::vector<uint32_t>& componentTypes, std::vector<BaseECSComponent*>& componentParam,
			std::vector<std::vector<uint8_t>*>& componentArrays);

		uint32_t findLeastCommonComponent(const std::vector<uint32_t>& componentTypes, const std::vector<uint32_t>& componentFlags);
		
		NULL_COPY_AND_ASSIGN(ECS);


	public:
		// MAKE ENTITIES
		template <class A>
		EntityHandle makeEntity(A& c1) {
			BaseECSComponent* components[] = { &c1};
			uint32_t componentIDs[] = { A::ID};
			return makeEntity(components, componentIDs, 1);
		};
		
	
		template <class A, class B>
		EntityHandle makeEntity(A& c1, B& c2) {
			BaseECSComponent* components[] = { &c1, &c2};
			uint32_t componentIDs[] = { A::ID, B::ID};
			return makeEntity(components, componentIDs, 2);
		};
		
		template <class A, class B, class C>
		EntityHandle makeEntity(A& c1, B& c2, C& c3) {
			BaseECSComponent* components[] = { &c1, &c2, &c3 };
			uint32_t componentIDs[] = { A::ID, B::ID, C::ID };
			return makeEntity(components, componentIDs, 3);
		};

		template <class A, class B, class C, class D>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4) {
			BaseECSComponent* components[] = { &c1, &c2, &c3, &c4};
			uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID};
			return makeEntity(components, componentIDs, 4);
		};

		template <class A, class B, class C, class D, class E>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5) {
			BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5};
			uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID};
			return makeEntity(components, componentIDs, 5);
		};


		template <class A, class B, class C, class D, class E, class F>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6) {
			BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6};
			uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID};
			return makeEntity(components, componentIDs, 6);
		};




		template <class A, class B, class C, class D, class E, class F, class G>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7) {
			BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7};
			uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID};
			return makeEntity(components, componentIDs, 7);
		};



		template <class A, class B, class C, class D, class E, class F, class G, class H>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8) {
			BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8 };
			uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID };
			return makeEntity(components, componentIDs, 8);
		};



		template <class A, class B, class C, class D, class E, class F, class G, class H, class I>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8, I& c9) {
			BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9,};
			uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID, I::ID };
			return makeEntity(components, componentIDs, 9);
		};


		template <class A, class B, class C, class D, class E, class F, class G, class H, class I, class J>
		EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8, I& c9, J& c10){
			BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9,&c10};
			uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID, I::ID, J::ID };
			return makeEntity(components, componentIDs, 10);
		};



	};

	template<class Component>
	inline void ECS::addComponent(EntityHandle entity, Component* component){
		addComponentInternal(entity, handleToEntity(entity), Component::ID, component);
	}

	template<class Component>
	inline bool ECS::removeComponent(EntityHandle entity)
	{
		return removeComponentInternal(entity, Component::ID);
	}

	template<class Component>
	inline Component* ECS::getComponent(EntityHandle entity){
		return (Component*)getComponentInternal(handleToEntity(entity),components[Component::ID], Component::ID);
	}
	*/

class ECSListener
{
public:
	virtual void onMakeEntity(EntityHandle handle) {}
	virtual void onRemoveEntity(EntityHandle handle) {}
	virtual void onAddComponent(EntityHandle handle, uint32_t id) {}
	virtual void onRemoveComponent(EntityHandle handle, uint32_t id) {}

	const std::vector<uint32_t>& getComponentIDs() {
		return componentIDs;
	}

	inline bool shouldNotifyOnAllComponentOperations() {
		return notifyOnAllComponentOperations;
	}
	inline bool shouldNotifyOnAllEntityOperations() {
		return notifyOnAllEntityOperations;
	}

protected:
	void setNotificationSettings(
		bool shouldNotifyOnAllComponentOperations,
		bool shouldNotifyOnAllEntityOperations) {
		notifyOnAllComponentOperations = shouldNotifyOnAllComponentOperations;
		notifyOnAllEntityOperations = shouldNotifyOnAllEntityOperations;
	}
	void addComponentID(uint32_t id) {
		componentIDs.push_back(id);
	}
private:
	std::vector<uint32_t> componentIDs;
	bool notifyOnAllComponentOperations = false;
	bool notifyOnAllEntityOperations = false;
};

class ECS
{
public:
	ECS() {}
	~ECS();

	// ECSListener methods
	inline void addListener(ECSListener* listener) {
		listeners.push_back(listener);
	}

	// Entity methods
	EntityHandle makeEntity(BaseECSComponent** components, const uint32_t* componentIDs, size_t numComponents);
	void removeEntity(EntityHandle handle);

	template<class A>
	EntityHandle makeEntity(A& c1)
	{
		BaseECSComponent* components[] = { &c1 };
		uint32_t componentIDs[] = { A::ID };
		return makeEntity(components, componentIDs, 1);
	}

	template<class A, class B>
	EntityHandle makeEntity(A& c1, B& c2)
	{
		BaseECSComponent* components[] = { &c1, &c2 };
		uint32_t componentIDs[] = { A::ID, B::ID };
		return makeEntity(components, componentIDs, 2);
	}

	template<class A, class B, class C>
	EntityHandle makeEntity(A& c1, B& c2, C& c3)
	{
		BaseECSComponent* components[] = { &c1, &c2, &c3 };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID };
		return makeEntity(components, componentIDs, 3);
	}

	template<class A, class B, class C, class D>
	EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4)
	{
		BaseECSComponent* components[] = { &c1, &c2, &c3, &c4 };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID };
		return makeEntity(components, componentIDs, 4);
	}

	template<class A, class B, class C, class D, class E>
	EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5)
	{
		BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5 };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID };
		return makeEntity(components, componentIDs, 5);
	}

	template<class A, class B, class C, class D, class E, class F>
	EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6)
	{
		BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6 };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID };
		return makeEntity(components, componentIDs, 6);
	}

	template<class A, class B, class C, class D, class E, class F, class G>
	EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7)
	{
		BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7 };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID };
		return makeEntity(components, componentIDs, 7);
	}

	template<class A, class B, class C, class D, class E, class F, class G, class H>
	EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8)
	{
		BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8 };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID };
		return makeEntity(components, componentIDs, 8);
	}

	template<class A, class B, class C, class D, class E, class F, class G, class H, class I>
	EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8, I& c9)
	{
		BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9 };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID, I::ID };
		return makeEntity(components, componentIDs, 9);
	}

	template<class A, class B, class C, class D, class E, class F, class G, class H, class I, class J>
	EntityHandle makeEntity(A& c1, B& c2, C& c3, D& c4, E& c5, F& c6, G& c7, H& c8, I& c9, J& c10)
	{
		BaseECSComponent* components[] = { &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8, &c9, &c10 };
		uint32_t componentIDs[] = { A::ID, B::ID, C::ID, D::ID, E::ID, F::ID, G::ID, H::ID, I::ID, J::ID };
		return makeEntity(components, componentIDs, 10);
	}



	// Component methods
	template<class Component>
	inline void addComponent(EntityHandle entity, Component* component)
	{
		addComponentInternal(entity, handleToEntity(entity), Component::ID, component);
		for (uint32_t i = 0; i < listeners.size(); i++) {
			const std::vector<uint32_t>& componentIDs = listeners[i]->getComponentIDs();
			if (listeners[i]->shouldNotifyOnAllComponentOperations()) {
				listeners[i]->onAddComponent(entity, Component::ID);
			}
			else {
				for (uint32_t j = 0; j < componentIDs.size(); j++) {
					if (componentIDs[j] == Component::ID) {
						listeners[i]->onAddComponent(entity, Component::ID);
						break;
					}
				}
			}
		}
	}

	template<class Component>
	bool removeComponent(EntityHandle entity)
	{
		for (uint32_t i = 0; i < listeners.size(); i++) {
			const std::vector<uint32_t>& componentIDs = listeners[i]->getComponentIDs();
			for (uint32_t j = 0; j < componentIDs.size(); j++) {
				if (listeners[i]->shouldNotifyOnAllComponentOperations()) {
					listeners[i]->onRemoveComponent(entity, Component::ID);
				}
				else {
					if (componentIDs[j] == Component::ID) {
						listeners[i]->onRemoveComponent(entity, Component::ID);
						break;
					}
				}
			}
		}
		return removeComponentInternal(entity, Component::ID);
	}

	template<class Component>
	Component* getComponent(EntityHandle entity)
	{
		return (Component*)getComponentInternal(handleToEntity(entity), components[Component::ID], Component::ID);
	}

	BaseECSComponent* getComponentByType(EntityHandle entity, uint32_t componentID)
	{
		return getComponentInternal(handleToEntity(entity), components[componentID], componentID);
	}

	// System methods
	void updateSystems(ECSSystemList& systems, float delta);

private:
	std::map<uint32_t, std::vector<uint8_t>> components;
	std::vector<std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t> > >* > entities;
	std::vector<ECSListener*> listeners;

	inline std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t> > >* handleToRawType(EntityHandle handle)
	{
		return (std::pair<uint32_t, std::vector<std::pair<uint32_t, uint32_t> > >*)handle;
	}

	inline uint32_t handleToEntityIndex(EntityHandle handle)
	{
		return handleToRawType(handle)->first;
	}

	inline std::vector<std::pair<uint32_t, uint32_t> >& handleToEntity(EntityHandle handle)
	{
		return handleToRawType(handle)->second;
	}

	void deleteComponent(uint32_t componentID, uint32_t index);
	bool removeComponentInternal(EntityHandle handle, uint32_t componentID);
	void addComponentInternal(EntityHandle handle, std::vector<std::pair<uint32_t, uint32_t> >& entity, uint32_t componentID, BaseECSComponent* component);
	BaseECSComponent* getComponentInternal(std::vector<std::pair<uint32_t, uint32_t> >& entityComponents, std::vector<uint8_t>& array, uint32_t componentID);

	void updateSystemWithMultipleComponents(uint32_t index, ECSSystemList& systems, float delta, const std::vector<uint32_t>& componentTypes,
		std::vector<BaseECSComponent*>& componentParam, std::vector<std::vector<uint8_t>*>& componentArrays);
	uint32_t findLeastCommonComponent(const std::vector<uint32_t>& componentTypes, const std::vector<uint32_t>& componentFlags);

	NULL_COPY_AND_ASSIGN(ECS);
};
}