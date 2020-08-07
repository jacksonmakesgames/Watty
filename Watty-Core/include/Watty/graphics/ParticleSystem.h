#pragma once
#include <glm.hpp>
#include <vector>
#include <graphics/Sprite.h>
//#include <graphics/ParticleRenderer.h>
#include <utils/Random.h>
#include <utils/Timer.h>

#include <graphics/Color.h>

namespace letc { namespace graphics {
	struct ParticleProperties
	{
		glm::vec2 position = {0,0};
		glm::vec2 velocity = {1,1};
		glm::vec2 velocityVariation = {1,1};
		float sizeVariation = .5f;
		WattyColor colorBegin = Color::white;
		WattyColor colorEnd = Color::transparent;
		float sizeBegin = 1;
		float sizeEnd = 0;
		float lifeTime = 2;
		float rotationSpeed = .2f;
		float rotationSpeedVariation = .2f;
		float rate = 1; // TODO less than one?
		unsigned int maxParticles = 2000;
		Texture* texture;

		~ParticleProperties() {
			delete texture;
		}
	};


	class ParticleSystem : public Renderable2D{
	private:
		struct Particle : public Renderable2D{
			glm::vec2 pSize = {1,1};
			glm::vec2 pPos = { 0, 0 };
			glm::vec2 velocity, velocityVariation = glm::vec2(0);
			float sizeVariation = 0;
			WattyColor colorBegin, colorEnd;
			float rotation = 0.0f;
			float sizeBegin, sizeEnd = 1.0f;
			float lifeTime = 1.0f;
			float lifeRemaining = 0.0f;
			float rotationSpeed = 0.0f;
			bool active = false;

			Particle() {
				Renderable2D::m_size = m_size;
			}
		};

		std::vector<Particle> mParticles;
		uint32_t mMaxParticles = 1200;
		uint32_t mPoolIndex = mMaxParticles-1;

	public:		
		ParticleProperties* properties;
	private:
		void submit(Renderer2D* renderer) const override;

	public:
		void update() override;
		void emitOne();
		void changeMaxParticles(unsigned int max);
		
		ParticleSystem(ParticleProperties* properties);




	};






} }