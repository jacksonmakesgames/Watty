#pragma once
#include <glm.hpp>
#include <vector>
#include <graphics/renderable2d.h>
#include <graphics/ParticleRenderer.h>
#include <utils/Random.h>

#include <graphics/Color.h>

namespace letc { namespace graphics {
	struct ParticleProperties
	{
		glm::vec2 position;
		glm::vec2 velocity, velocityVariation;
		float sizeVariation;
		WattyColor colorBegin, colorEnd;
		float sizeBegin, sizeEnd;
		float lifeTime;
		float rotationSpeed;

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

		
	private:
		void submit(Renderer2D* renderer) const override;
		ParticleRenderer* m_renderer;
		
	public:
		void update(double deltaTime);
		void emitOne(const ParticleProperties& properties);
		inline void changeMaxParticles(unsigned int max) { mParticles = std::vector<Particle>(); mParticles.resize(max); mPoolIndex = max - 1; mMaxParticles = max; }
		
		ParticleSystem(uint32_t maxParticles);




	};






} }