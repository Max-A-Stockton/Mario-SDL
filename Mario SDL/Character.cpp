#include "Character.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	mCollisionRadius = 15.0f;
	mCanJump = true;
	mJumping = false;
	mCurrentLevelMap = map;
}


Character::~Character()
{
	mRenderer = NULL;
}

void Character::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= moveSpeed;
}
void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += moveSpeed;
}

void Character::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::AddGravity(float deltaTime)
{
	if (mPosition.y + 64 <= SCREEN_HEIGHT)
	{
		mPosition.y += GRAVITY_STRENGTH * deltaTime;
	}
	else
	{
		mCanJump = true;
	}
}

float Character::GetCollisionRadius()
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

void Character::CancelJump()
{
	mJumpForce = 0.0f;
}

void Character::Render()
{
	mTexture->Render(GetPosition(), SDL_FLIP_NONE, 0.0f);

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
}


/*void Character::Update(float deltaTime, SDL_Event e)
{
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
				if (mCanJump)
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

		AddGravity(deltaTime);

	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		MoveRight(deltaTime);
	}
}*/

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
	return mPosition;
}