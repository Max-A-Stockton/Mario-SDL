#pragma once
#ifndef _CHARACTER_MARIO
#define _CHARACTER_MARIO
#include "Character.h"
class CharacterMario : public Character
{
public: 
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();
	void Update(float deltaTime, SDL_Event e);
	

private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
};

#endif _CHARACTER_MARIO