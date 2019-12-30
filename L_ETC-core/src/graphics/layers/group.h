#pragma once
#include "../renderable2d.h"
#include "../../GameObject.h"

namespace letc {
	class Group : public GameObject {
	private:
	public:
		Group(const math::Matrix4& transform);
		~Group();
		void add(GameObject* gameObject);
		void submit(graphics::Renderer2D* renderer) const override;

		void update() override;

		std::vector<GameObject*> m_childrenGameObjects;
		inline const std::vector<GameObject*>& getChildren()const { return m_childrenGameObjects; }

	};
}