#include "audiomanager.h"
namespace letc {namespace audio {
	
	/*gau_Manager* AudioManager::m_manager	= nullptr;
	ga_Mixer* AudioManager::m_mixer			= nullptr;*/

	SoLoud::Soloud* AudioManager::soloud = new SoLoud::Soloud;

	std::vector<AudioClip*> AudioManager::m_clips;

	void AudioManager::init()
	{
		/* Initialize library + manager */
		//TODO: handle error
		//gc_initialize(0);

		//m_manager = gau_manager_create();
		//m_mixer = gau_manager_mixer(m_manager);
		soloud->init();
	
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
		//gau_manager_destroy(m_manager);
		//gc_shutdown();
		for (size_t i = 0; i < m_clips.size(); i++){
			delete m_clips[i];
		}

		soloud->deinit();           // clean-up
		delete soloud;              // this cleans up too
	}

	void AudioManager::update(){
		//gau_manager_update(m_manager);
	}

}}