#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"
#include "Texture2D.h"

class Texture2D;

class Character
{
private:
	bool mMovingLeft;
	bool mMovingRight;
	const float moveSpeed = 0.05f;

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	FACING mFacingDirection;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	void AddGravity(float deltaTime);
	bool mJumping;
	bool mCanJump;
	void Jump();
	float mJumpForce;
	float mCollisionRadius;
	LevelMap* mCurrentLevelMap;

public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	Rect2D GetCollisionBox();
	
	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	bool IsJumping() { return mJumping == true; }
	void CancelJump();

	float GetCollisionRadius();
};

