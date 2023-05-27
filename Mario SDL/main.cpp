#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include <iostream>
#include "GameScreenManager.h"

using namespace std;

//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;
//Texture2D* gTexture = NULL;

//Function Prototypes
bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//All good so attempt to create a window.
		gWindow = SDL_CreateWindow("Mario SDL",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			//Nope.
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL)
		{
			//Initialise PNG Loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
	}
	

	//Load background texture
	/*gTexture = new Texture2D(gRenderer);
	if (!gTexture->LoadFromFile("Assets/test.bmp"))
	{
		return false;
	}*/

	
	
	return true;
}
void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	//Update the screen
	SDL_RenderPresent(gRenderer);
}
void CloseSDL()
{
	/*Release Texture
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;*/
	
	//Release renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	
	//Release Window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Destroy game screen manager
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
bool Update()
{
	//Get the new time
	Uint32 newTime = SDL_GetTicks();

	//Event Handler
	SDL_Event e;

	
	//Get the events
	SDL_PollEvent(&e);
//Handle any events
	switch (e.type)
	{
		//Click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	}
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	//Set the current time to be old time
	gOldTime = newTime;
	return false;
}
int main(int argc, char* argv[])
{
	if (InitSDL())
	{
		//Set up game screen manager
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
		gOldTime = SDL_GetTicks();
		//Flag to check if we wish to quit
		bool quit = false;

		//Game Loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	
	//Close window and free resources
	CloseSDL();
	return 0;
}