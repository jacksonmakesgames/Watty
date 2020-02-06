#pragma once
#include <ext/glm/include/glm.hpp>
#include <vector>
#include <graphics/renderable2d.h>

namespace letc { namespace graphics {
	struct ParticleProperties
	{
		glm::vec3 position;
		glm::vec2 velocity, velocityVariation;
		glm::vec4 colorBegin, colorEnd;
		float sizeBegin, sizeEnd;
		float lifeTime;
		float rotationSpeed;

	};


	class ParticleSystem : public Renderable2D{
	private:
		struct Particle : public Renderable2D{
			glm::vec3 velocity, velocityVariation;
			glm::vec4 colorBegin, colorEnd;
			float rotation = 0.0f;
			float sizeBegin, sizeEnd;
			float lifeTime;
			float lifeRemaining = 0.0f;
			float rotationSpeed;
			bool active = false;

		};

		std::vector<Particle> mParticles;
		uint32_t mMaxParticles = 1000;
		uint32_t mPoolIndex = mMaxParticles-1;

		
	private:
		void update(double deltaTime);
		void submit(Renderer2D* renderer) const override;

		void emitOne(const ParticleProperties& properties);


	public:
		ParticleSystem(uint32_t maxParticles);



	};






} }