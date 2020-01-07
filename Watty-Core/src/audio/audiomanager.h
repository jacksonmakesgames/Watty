#pragma once
#include <vector>
#include "audioclip.h"

#include "../../ext/soloud/include/soloud/soloud.h"
#include "../../ext/soloud/include/soloud/soloud_wav.h"

namespace letc{ namespace audio{
	class AudioManager{


	private:
		friend class AudioClip;
		static std::vector<AudioClip*> m_clips;
		static SoLoud::Soloud* soloud;

		//static gau_Manager* m_manager;
		//static ga_Mixer* m_mixer;
		
	public:
		static void init();
		static void addClip(AudioClip* clip);
		static AudioClip* getClip(const std::string& name);
		static void clean();
		static void update();

		inline const std::vector<AudioClip*>& getAllClips() { return m_clips; }
	private:
		AudioManager() {}
	};
	

} }