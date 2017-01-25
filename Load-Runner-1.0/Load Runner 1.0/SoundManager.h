#ifndef INC_SHADY_ENGINE_SOUND_MANAGER_H
#define INC_SHADY_ENGINE_SOUND_MANAGER_H


#include<irrKlang.h>
#include<string>

	class SoundManager
	{

	public:

		SoundManager();

		~SoundManager();

		void init();

		void play_sfx(const std::string& pLocation) const;

		void play_music(const std::string& pLocation)const;

	private:

		irrklang::ISoundEngine *mEngine;
	};


#endif