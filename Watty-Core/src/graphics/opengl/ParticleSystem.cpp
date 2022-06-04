#include <graphics/ParticleSystem.h>

namespace watty { namespace graphics {
	ParticleSystem::ParticleSystem(ParticleProperties* props) :
		properties(props)
	{
		mMaxParticles = properties->maxParticles;
		mParticles.resize(mMaxParticles);
		mPoolIndex = mMaxParticles - 1;
	}

	void ParticleSystem::submit(Renderer2D* renderer)const {
		int j = 0;
		for (int i = mPoolIndex; j < mMaxParticles; i--) {
			if (i < 0) i = mMaxParticles - 1;
			Particle particle = mParticles[i];
			if (particle.active) {
				//color:
				float life = particle.lifeRemaining / particle.lifeTime;
				WattyColor color = Color::lerp(particle.colorEnd, particle.colorBegin, life);
				particle.setColor(color);

				particle.pSize = glm::vec2(glm::mix(particle.sizeEnd, particle.sizeBegin, life));


				glm::mat4 transform = glm::mat4(1.0f);
				transform = glm::translate(transform, glm::vec3(particle.pPos.x, particle.pPos.y, 0.0f));

				transform = glm::translate(transform, glm::vec3(0.5f * particle.pSize.x, 0.5f * particle.pSize.y, 0.0f));
				transform = glm::rotate(transform, particle.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
				transform = glm::translate(transform, glm::vec3(-0.5f * particle.pSize.x, -0.5f * particle.pSize.y, 0.0f));
				transform = glm::scale(transform, glm::vec3(particle.pSize, 1.0f));

				if (properties->texture != nullptr) {
					Sprite sprite = Sprite({ 0,0 }, { 1,1 }, properties->texture);
					sprite.setColor(particle.getColor());
					renderer->push(transform);
					renderer->submit(&sprite);
					renderer->pop();
				}
				else {
					Sprite sprite = Sprite({ 0,0 }, { 1,1 }, particle.getColor());
					renderer->push(transform);
					renderer->submit(&sprite);
					renderer->pop();


				}
			}
				j++;
		}
	}

	void ParticleSystem::emitOne(){
		Particle& particle = mParticles[mPoolIndex];
		particle.active = true;

		particle.pPos = properties->position;
		particle.rotation = properties->rotationSpeedVariation * Random::range(-.5f, .5f);

		particle.velocity = properties->velocity;
		particle.velocityVariation = properties->velocityVariation;
		particle.velocity.x += properties->velocityVariation.x * Random::range(-.5f,.5f);
		particle.velocity.y += properties->velocityVariation.y * Random::range(-.5f,.5f);

		particle.colorBegin = properties->colorBegin;
		particle.colorEnd = properties->colorEnd;

		particle.lifeTime = properties->lifeTime;
		particle.lifeRemaining = properties->lifeTime;
		
		particle.sizeVariation = properties->sizeVariation;
		particle.sizeBegin = properties->sizeBegin + particle.sizeVariation * Random::range(-.5f, .5f);
		particle.sizeEnd = properties->sizeEnd;
		particle.pSize = glm::vec2(properties->sizeBegin);
		
		particle.rotationSpeed = properties->rotationSpeed;
		mPoolIndex = --mPoolIndex % mParticles.size();
	}

	void ParticleSystem::update(){
		double dt = Timer::delta;
		
		if (mMaxParticles != properties->maxParticles)
			changeMaxParticles(properties->maxParticles);

		for (size_t i = 0; i < properties->rate; i++)
			emitOne();
		
		for (auto& particle : mParticles){
			if (!particle.active) continue;
			particle.lifeRemaining -= dt;
			if (particle.lifeRemaining <= 0.0f) {
				particle.active = false;
				continue;
			}
			particle.pPos		+= (particle.velocity				*	(float)dt);
			particle.rotation	+= (particle.rotationSpeed			*	(float)dt);
			
		}
	}

	void ParticleSystem::changeMaxParticles(unsigned int max) {
		mParticles = std::vector<Particle>(); mParticles.resize(max); mPoolIndex = max - 1; mMaxParticles = max;
	}
	
}}