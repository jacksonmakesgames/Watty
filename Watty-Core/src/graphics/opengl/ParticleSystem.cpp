#include <graphics/ParticleSystem.h>

namespace letc { namespace graphics {
	ParticleSystem::ParticleSystem(uint32_t maxParticles) : mMaxParticles(maxParticles)
	{
		mParticles.resize(mMaxParticles);
		mPoolIndex = mMaxParticles - 1;
	}

	void ParticleSystem::submit(Renderer2D* renderer)const{
		bool emptyMat = m_transformationMatrix == glm::mat4(1);
		if (!emptyMat)
			renderer->push(m_transformationMatrix);
		
		for (size_t i = 0; i < mParticles.size(); i++){
			if (mParticles[i].active) {
				//Draw 
				renderer->submit(&mParticles[i]);
			}

		}
		renderer->submit(this);
		
		if (!emptyMat)
			renderer->pop();
	}

	void ParticleSystem::emitOne(const ParticleProperties& properties){
		Particle& particle = mParticles[mPoolIndex];
		particle.active = true;
		particle.position = properties.position;
		particle.rotation = 

		mPoolIndex++;
	}

	void ParticleSystem::update(double deltaTime){
		for (auto& particle : mParticles)
		{
			if (!particle.active) continue;
			if (particle.lifeRemaining <= 0.0f) {
				particle.active = false;
				continue;
			}
			particle.lifeRemaining -= deltaTime;
			particle.position += (particle.velocity			*	(float)deltaTime);
			particle.rotation += (particle.rotationSpeed	*	(float)deltaTime);
		}
	}
}}