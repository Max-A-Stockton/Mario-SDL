#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
using namespace::std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	//mTexture = NULL;
	mWidth;
	mHeight;
}

bool Texture2D::LoadFromFile(string path)
{
	//Remove the memory used for a previous texture.
	Texture2D::Free();


	//Load the image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		//Colour key the image - The colour to be transparent
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		//Set dimensions
	
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		mWidth = pSurface->w;
		mHeight = pSurface->h;
		//Remove loaded surace
		SDL_FreeSurface(pSurface);
	}
	return mTexture != NULL;
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);

	//mTexture->Render(Vector2D(), SDL_FLIP_NONE);

}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	//render to the screen
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}

void Texture2D::Free()
{
	//Check if texture exists before removing it
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		
	}
}

Texture2D::~Texture2D()
{
	//Free up memory
	Free();

	mRenderer = NULL;
}