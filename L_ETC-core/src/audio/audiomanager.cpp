#include "audiomanager.h"
namespace letc {namespace audio {
	
	gau_Manager* AudioManager::m_manager	= nullptr;
	ga_Mixer* AudioManager::m_mixer			= nullptr;

	std::vector<AudioClip*> AudioManager::m_clips;

	void AudioManager::init()
	{
		/* Initialize library + manager */
		//TODO: handle error
		gc_initialize(0);

		m_manager = gau_manager_create();
		m_mixer = gau_manager_mixer(m_manager);
	}
	void AudioManager::addClip(AudioClip* clip) {
		m_clips.push_back(clip);
	}

	AudioClip* AudioManager::getClip(const std::string& name)
	{
		for (size_t i = 0; i < m_clips.size(); i++){
			if (name == m_clips[i]->getName()) return m_clips[i];
		}
	}

	void AudioManager::clean(){
		gau_manager_destroy(m_manager);
		gc_shutdown();
		for (size_t i = 0; i < m_clips.size(); i++){
			delete m_clips[i];
		}
	}

	void AudioManager::update(){
		gau_manager_update(m_manager);
		gc_thread_sleep(1);
	}

}}