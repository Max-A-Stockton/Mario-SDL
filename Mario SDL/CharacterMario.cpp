#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	
}

CharacterMario::~CharacterMario()
{

}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	//Collision Detection Variables
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;
	int headPosition = mPosition.y / TILE_HEIGHT;

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = true;
			break;
		case SDLK_RIGHT:
			mMovingRight = true;
			break;
		case SDLK_UP:
			if (mCanJump && !mJumping)
				Jump();
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		}
		break;
	}
	//Deal with Jumping first
	if (mJumping)
	{
		//Adjust the position
		mPosition.y -= mJumpForce * deltaTime;

		//Reduce the jump force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//Has the jump force reduced to 0?
		if (mJumpForce <= 0.0f)
			mJumping = false;
	}

	if (!mCurrentLevelMap->GetTileAt(footPosition, centralXPosition))
	{
		AddGravity(deltaTime);
	}
	if (mCurrentLevelMap->GetTileAt(headPosition, centralXPosition))
	{
		mJumpForce = 0;
	}
	else
	{
		//Collided with ground so can jump
		mCanJump = true;
	}

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}
}
