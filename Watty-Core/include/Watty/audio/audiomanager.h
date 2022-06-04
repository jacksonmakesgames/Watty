#pragma once

#include <vector>
#include "audioclip.h"
#include<iostream>

#include <soloud.h>
#include <soloud_wav.h>


namespace watty{ namespace audio{
	class AudioManager{


	private:
		friend class AudioClip;
		static std::vector<AudioClip*> m_clips;
		static SoLoud::Soloud* soloud;
	public:
		static bool initialized;
		static void init();
		static void addClip(std::string name, const char* path);
		static AudioClip* getClip(const std::string& name);
		static void clean();
		static void update();

		inline const std::vector<AudioClip*>& getAllClips() { return m_clips; }
	private:
		AudioManager() {}
	};
	

} }
