#include "audioclip.h"

namespace letc {namespace audio {

	AudioClip::AudioClip(const std::string& name, const std::string& filepath){
		m_name = name;
		m_filepath = filepath;
		m_playing = false;
		std::vector<std::string> split = split_string(m_filepath, '.');

		int returnCode = wavFile.load(filepath.c_str());

		if (returnCode == SoLoud::FILE_NOT_FOUND) {
			printf("Couldn't find audio file: " );
			printf(filepath.c_str());
			printf("\n");
		}
	}

	AudioClip::~AudioClip(){
		wavFile.stop();
	}

	void AudioClip::play(bool loop){
		m_playing = true;
		wavFile.setLooping(loop);
		m_handle = AudioManager::soloud->play(wavFile);
	}

	void AudioClip::resume() {
		if (m_playing) return;
		
		AudioManager::soloud->setPause(m_handle, false);
	}
	
	void AudioClip::pause() {
		if (!m_playing) return;
		m_playing = false;
		AudioManager::soloud->setPause(m_handle, true);
	}

	void AudioClip::stop(){
		m_playing = false;
		wavFile.stop();

	}

	void AudioClip::setGain(float gain) {
		if (gain <= 0) gain = 0;
		m_gain = gain;
		wavFile.setVolume(m_gain);
		AudioManager::soloud->fadeVolume(m_handle, m_gain, 0);
	}

	   	


}}