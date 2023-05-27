#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;

	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpiteHeight = mTexture->GetHeight();
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;

		mJumping = true;
		mCanJump = true;
	}
}

void CharacterKoopa::FlipRightWayUp()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mFacingDirection = FACING_LEFT;
	}
	else if (mFacingDirection == FACING_LEFT)
	{
		mFacingDirection = FACING_RIGHT;
	}

	mInjured = false;
	Jump();
}

void CharacterKoopa::SetDead()
{
	mDead = true;
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	if (!mInjured)
	{
		//Not injured so move
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else
	{
		//Don't move when injured
		mMovingRight = false;
		mMovingLeft = false;

		//Count down the injured time
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
			FlipRightWayUp();

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

void CharacterKoopa::Render()
{
	//Variable to hold the left position of the sprite we want to draw
	float left = 0.0f;

	//If injured move the left position to be the left position of the second image of the spritesheet
	if (mInjured)
		left = mSingleSpriteWidth;

	//Get the portion of the spritesheet you want to draw
	//								{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpiteHeight };

	//Determine where it is drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteWidth };

	//Draw it facing correct direction
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}