#include "audioclip.h"

namespace letc {namespace audio {

	void setFlagAndDestroyOnFinish(ga_Handle * in_handle, void* in_context);

	AudioClip::AudioClip(const std::string& name, const std::string& filepath){
		m_name = name;
		m_filepath = filepath;
		m_playing = false;
		std::vector<std::string> split = split_string(m_filepath, '.');
		m_sound = gau_load_sound_file(filepath.c_str(), split.back().c_str());
		if (m_sound == nullptr) {
			printf("Couldn't find audio file: " );
			printf(filepath.c_str());
			printf("\n");
		}
	}

	AudioClip::~AudioClip(){
		//if(m_sound)
		//	ga_sound_release(m_sound);
		//if(m_handle)
		//ga_handle_destroy(m_handle); // TODO: not sure
	}

	void AudioClip::play(bool loop){
		if (m_sound == nullptr) return;
		m_playing = true;
		m_looping = loop;
		gc_int32 quit = 0;
		gau_SampleSourceLoop* loopSrc = 0;
		gau_SampleSourceLoop** pLoopSrc = &loopSrc;

		if (!m_looping)
			pLoopSrc = 0;

		m_handle = gau_create_handle_sound(AudioManager::m_mixer, m_sound, &setFlagAndDestroyOnFinish, &quit, pLoopSrc);
		ga_handle_play(m_handle);
	}

	void AudioClip::resume() {
		// Note, the engine WILL crash if the song is not currently playing or paused. Use Play() to start playing a song
		if (m_playing) return;
		
		play(m_looping);
		ga_handle_seek(m_handle, m_SeekPosition);
	}
	
	void AudioClip::pause() {
		if (!m_playing || m_handle->state == 5) return;
		m_playing = false;
		m_SeekPosition = ga_handle_tell(m_handle, GA_TELL_PARAM_CURRENT);
		ga_handle_stop(m_handle);
	}

	void AudioClip::stop(){
		if (!m_playing || m_handle->state == 5) return;
		m_playing = false;
		ga_handle_stop(m_handle);
		setFlagAndDestroyOnFinish(m_handle, m_handle->context);

	}

	void AudioClip::setGain(float gain) {
		if (!m_playing || m_handle->state == 5) return;
		if (gain <= 0) gain = 0;
		m_gain = gain;
		ga_handle_setParamf(m_handle, GA_HANDLE_PARAM_GAIN, gain);
	}


	void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context){
		//m_playing = false;

		gc_int32* flag = (gc_int32*)(in_context);
		*flag = 1;
		ga_handle_destroy(in_handle);
	}

	


}}