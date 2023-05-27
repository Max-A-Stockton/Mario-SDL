#pragma once
#ifndef _CHARACTER_KOOPA
#define _CHARACTER_KOOPA
#include "Character.h"
class CharacterKoopa : public Character
{
private:
	float mSingleSpriteWidth;
	float mSingleSpiteHeight;

	float mMovementSpeed;

	bool mInjured;
	bool mInjuredTime;
	bool mDead;

	bool mMovingLeft;
	bool mMovingRight;

	void FlipRightWayUp();

public:

	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	bool GetInjured() { return mInjured; }
	bool GetAlive() { return mDead; }
	
	void SetDead();

	void TakeDamage();
	void Jump();

	void Render();
	void Update(float deltaTime, SDL_Event e);

};

#endif _CHARACTER_KOOPA