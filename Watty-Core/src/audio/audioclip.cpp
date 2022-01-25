
#include <audio/audioclip.h>
namespace watty {namespace audio {
	AudioClip::AudioClip(const std::string& name, const std::string& filepath, SoLoud::Soloud* soloudPtr):
		m_soloudPtr(soloudPtr), m_name(name), m_filepath(filepath), m_playing(false)
	{
		init();
	}

	void AudioClip::stop() {
		m_playing = false;
		wavFile.stop();
	}

	AudioClip::~AudioClip(){
		wavFile.stop();
	}
	
	void AudioClip::play(bool loop){
		m_playing = true;
		wavFile.setLooping(loop);
		m_handle = m_soloudPtr->play(wavFile);
	}


	void AudioClip::resume() {
		if (m_playing) return;
		m_soloudPtr->setPause(m_handle, false);
	}


	void AudioClip::pause() {
		if (!m_playing) return;
		m_playing = false;
		
		m_soloudPtr->setPause(m_handle, true);
	}

	
	void AudioClip::setGain(float gain) {
		if (gain <= 0) gain = 0;
		m_gain = gain;
		wavFile.setVolume(m_gain);
		m_soloudPtr->fadeVolume(m_handle, m_gain, 0);
	}

	void AudioClip::init(){
		std::vector<std::string> split = split_string(m_filepath, '.');
#ifdef WATTY_EMSCRIPTEN
		int returnCode = wavFile.load(m_filepath.c_str());
#else
		Resource* res = Resources::Load(m_filepath.c_str());
		if (res == nullptr) {
			//TODO log error
			std::cout << "Could not find audio file: " << m_filepath << std::endl;
			return;
		}
		int returnCode = wavFile.loadMem(res->data, res->size/8,false, false);
		if (returnCode != SoLoud::SO_NO_ERROR) {
			//TODO: log error
			std::cout << "Error loading audio resource: " << m_soloudPtr->getErrorString(returnCode) << std::endl;

		}
#endif
	}



	   	


}}
