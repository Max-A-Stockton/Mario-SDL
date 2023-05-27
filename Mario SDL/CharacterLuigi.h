#pragma once
#ifndef _CHARACTER_LUIGI
#define _CHARACTER_LUIGI
#include "Character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();
	void Update(float deltaTime, SDL_Event e);
	

private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
};

#endif _CHARACTER_LUIGI
