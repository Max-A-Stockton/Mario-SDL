#pragma once
#include "Commons.h"
#include "Constants.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

class SoundManager
{
private:

	Mix_Music* gMusic = NULL;
	
	SoundManager();
	~SoundManager();

	void Play(std::string soundPath);

public:

};

