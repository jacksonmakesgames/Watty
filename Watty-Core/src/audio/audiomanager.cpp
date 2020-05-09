#include <audio/audiomanager.h>

namespace letc {namespace audio {
	class AudioClip;
	bool AudioManager::initialized = false;

	SoLoud::Soloud* AudioManager::soloud = new SoLoud::Soloud;

	std::vector<AudioClip*> AudioManager::m_clips;

	void AudioManager::init(){
		SoLoud::result result = soloud->init();

		if (result != SoLoud::SO_NO_ERROR) {
			//TODO log error
			std::cout << "AudioManager failed to initialize: Soloud initialization returned error: " << soloud->getErrorString(result) << std::endl;
			return;
		}
		else {
			std::cout << "Audiomanager initialized: " << soloud->getErrorString(result) << std::endl;
			initialized = true; // No error
		}
	}


	void AudioManager::addClip(std::string name, const char* path) {
		if (!initialized) init();
		m_clips.push_back(new AudioClip(name, path, soloud));
	}


	AudioClip* AudioManager::getClip(const std::string& name)
	{
		for (size_t i = 0; i < m_clips.size(); i++){
			if (name == m_clips[i]->getName()) return m_clips[i];
		}
		//todo: log error
		std::cout << "Could not find clip: " << name << ", returning NULLPTR" << std::endl;
		return nullptr;
	}


	void AudioManager::clean(){
		for (size_t i = 0; i < m_clips.size(); i++){
			delete m_clips[i];
		}
		soloud->stopAll();
		soloud->deinit();           // clean-up
		delete soloud;              // this cleans up too

	}


	void AudioManager::update(){
	}

}}
