#include <graphics/ParticleSystem.h>

namespace letc { namespace graphics {
	ParticleSystem::ParticleSystem(uint32_t maxParticles) : mMaxParticles(maxParticles)
	{
		mParticles.grow(mMaxParticles);
		mPoolIndex = mMaxParticles - 1;
		m_renderer = new ParticleRenderer();
	}

	void ParticleSystem::submit(Renderer2D* renderer)const{
		m_renderer->begin();

		//for (int i = mParticles.size()-1; i > 0; i--) {
		int j = 0;
		for (int i = mPoolIndex; j < mMaxParticles; i--) {
			if (i < 0) i = mMaxParticles-1;
			//if(i>=mParticles.size()) i = 0;
			Particle particle = mParticles[i];
			if (particle.active) {
				//color:
				float life = particle.lifeRemaining / particle.lifeTime;
				WattyColor color = Color::lerp(particle.colorEnd, particle.colorBegin, life);
				//color.rgba.a = color.rgba.a * life;
				particle.setColor(color);

		/*		glm::vec3 origin = glm::vec3(particle.pPos.x+particle.pSize.x/2.0f, particle.pPos.y+particle.pSize.y/2.0f, particle.pPos.z);
				glm::mat4 rot = glm::rotate(glm::mat4(1), particle.rotation, glm::vec3(0, 0, -1));
				rot = glm::translate(glm::mat4(1), origin) * rot * glm::translate(glm::mat4(1), -origin);
				*/
				particle.pSize = glm::vec2(glm::mix(particle.sizeEnd, particle.sizeBegin, life));
				

				glm::mat4 transform = glm::mat4(1.0f);
				transform = glm::translate(transform, glm::vec3(particle.pPos.x - .5f*particle.pSize.x,particle.pPos.y - .5f*particle.pSize.y, 0.0f));

				transform = glm::translate(transform, glm::vec3(0.5f * particle.pSize.x, 0.5f * particle.pSize.y, 0.0f));
				transform = glm::rotate(transform, particle.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
				transform = glm::translate(transform, glm::vec3(-0.5f * particle.pSize.x, -0.5f * particle.pSize.y, 0.0f));
				transform = glm::scale(transform, glm::vec3(particle.pSize, 1.0f));

				
				/*	glm::translate(glm::mat4(1.0f), { particle.pPos.x, particle.pPos.y, 0 })
					* glm::rotate(glm::mat4(1.0f), particle.rotation, glm::vec3(0, 0, 1))
					* glm::scale(glm::mat4(1.0f), { particle.pSize.x, particle.pSize.y, 1.0f });*/
				m_renderer->submit(transform, particle.getColor().c, particle.pSize);
			}
			j++;
		}


		m_renderer->end();
		m_renderer->flush();
		
	}

	void ParticleSystem::emitOne(const ParticleProperties& properties){
		Particle& particle = mParticles[mPoolIndex];
		particle.active = true;
		//particle.position = m_position + properties.position;
		particle.pPos = properties.position;// -glm::vec3(m_size.x, m_size.y, 1) / 2.0f;
		particle.rotation = Random::range(0.0f, 1.0f);

		particle.velocity = properties.velocity;
		particle.velocityVariation = properties.velocityVariation;
		particle.velocity.x += properties.velocityVariation.x * Random::range(-.5f,.5f);
		particle.velocity.y += properties.velocityVariation.y * Random::range(-.5f,.5f);

		particle.colorBegin = properties.colorBegin;
		particle.colorEnd = properties.colorEnd;

		particle.sizeVariation = properties.sizeVariation;
		particle.lifeTime = properties.lifeTime;
		particle.lifeRemaining = properties.lifeTime;
		particle.sizeBegin = properties.sizeBegin + particle.sizeVariation * Random::range(-.5f, .5f);
		particle.sizeEnd = properties.sizeEnd;
		//particle.size = glm::vec2(properties.sizeBegin);
		particle.pSize = glm::vec2(properties.sizeBegin);
		particle.rotationSpeed = properties.rotationSpeed;
		mPoolIndex = --mPoolIndex % mParticles.size();
	}

	void ParticleSystem::update(double deltaTime){
		for (auto& particle : mParticles)
		{
			if (!particle.active) continue;
			particle.lifeRemaining -= deltaTime;
			if (particle.lifeRemaining <= 0.0f) {
				particle.active = false;
				continue;
			}
			//particle.position += (particle.velocity			*	(float)deltaTime);
			particle.pPos += (particle.velocity			*	(float)deltaTime);
			particle.rotation += (particle.rotationSpeed	*	(float)deltaTime);
			
		}
	}

	
}}