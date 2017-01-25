#include "SoundManager.h"


using namespace irrklang;


	SoundManager::SoundManager()
	{
		mEngine = createIrrKlangDevice();
		
		init();
	}


	SoundManager::~SoundManager()
	{
		mEngine->drop();
	}


	void SoundManager::init()
	{
		mEngine = createIrrKlangDevice();

		if (!mEngine)
			throw std::runtime_error("failed to initialize sound manager!");
	}

	void SoundManager::play_sfx(const std::string & pLocation) const
	{
		mEngine->play2D(pLocation.c_str());
	}

	void SoundManager::play_music(const std::string & pLocation) const
	{
		mEngine->play2D(pLocation.c_str(),true);
	}


