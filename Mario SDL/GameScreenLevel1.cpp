#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Commons.h"
#include "Collisions.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	mLevelMap = NULL;
}
GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;
	delete mario;
	mario = NULL;
	delete luigi;
	luigi = NULL;
	delete mPowBlock;
	mPowBlock = NULL;
	mEnemies.clear();
}
bool GameScreenLevel1::SetUpLevel()
{
	
	
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Assets/BackgroundMB.png"))
	{
		std::cout << "Failed to load Background Texture";
		return false;
	}

	//Create level map
	SetLevelMap();

	//Set up the player characters
	mario = new CharacterMario(mRenderer, "Assets/Mario.png", Vector2D(64, 300), mLevelMap);
	luigi = new CharacterLuigi(mRenderer, "Assets/Luigi.png", Vector2D(200, 300), mLevelMap);
	//Set up 2 koopas
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_RIGHT, KOOPA_SPEED);

	//Set up Pow Block
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
	mScreenShake = false;
	mBackgroundYPos = 0.0f;

	return true;
}
void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
										{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

	//Clear up old map
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//set up new map
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	//Local Variable
	CharacterKoopa* ptrTempKoopa = new CharacterKoopa(mRenderer, "Assets/Koopa.png", position, mLevelMap, direction, speed);
	mEnemies.push_back(ptrTempKoopa);
}

void GameScreenLevel1::DoScreenShake()
{
	mScreenShake = true;
	mScreenShakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			//Collided whilst jumping
			if(mario->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				mario->CancelJump();

			}
		}
	}
}


void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//Check if enemy is on the bottom row of tiles
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				//Is the enemy offscreen to the left / right?
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))
				{
					mEnemies[i]->SetDead();
				}
			}

			//Now update
			mEnemies[i]->Update(deltaTime, e);

			//Check if enemy collides with player
			if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignore collisions if enemy is behind a pipe
			}
			else
			{
				/*if (Collisions::Instance()->Circle(mEnemies[i]->GetInjured() = true, mario))
				{
					mEnemies[i]->SetDead();
				}*/
			}

			//If enemy is no longer alive, schedule for deletion
			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//Remove dead enemies each update
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::Render()
{
	//Draw enemies
	for(unsigned int i = 0; i < mEnemies.size(); i++)
	{
		if (!mEnemies[i] == NULL)
			mEnemies[i]->Render();
	}
	
	//Draw the Background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	//Render the player
	mario->Render();
	luigi->Render();
	mPowBlock->Render();
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Do Screenshake if required
	if (mScreenShake)
	{
		mScreenShakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		//End the shake after the duration
		if (mScreenShakeTime <= 0.0f)
		{
			mScreenShake = false;
			mBackgroundYPos = 0.0f;
		}
	}
	
	//Update the player
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	//Update PowBlock
	UpdatePowBlock();
	//Update Enemies
	UpdateEnemies(deltaTime, e);

}
