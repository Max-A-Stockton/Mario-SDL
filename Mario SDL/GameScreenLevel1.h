#pragma once
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "LevelMap.h"
#include <vector>


class Character;
class Texture2D;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
	CharacterMario* mario;
	CharacterLuigi* luigi;

	void SetLevelMap();
	LevelMap* mLevelMap;

	void UpdatePowBlock();
	PowBlock* mPowBlock;

	bool mScreenShake;
	float mScreenShakeTime;
	float mWobble;
	float mBackgroundYPos;
	void DoScreenShake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	std::vector<CharacterKoopa*> mEnemies;

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};