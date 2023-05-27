#include "PowBlock.h"

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Assets/PowBlock.png";
	mTexture = new Texture2D(renderer);
	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture: " << imagePath << std::endl;
		return;
	}
	
	mLevelMap = map;
	mSingleSpriteWidth = mTexture->GetWidth() / 3;//3 sprites on sprite sheet in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);

}
PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}

Rect2D PowBlock::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft -= 1;

	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		mLevelMap->ChangeTileAt(8, 7, 8);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}

void PowBlock::Render()
{
	//Get the portion of spritesheet to be drawn
	int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

	//								{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
	SDL_Rect portionOfSpriteSheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	
	//Determine where the pow block is drawn
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	//Draw Pow Block
	mTexture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
}
