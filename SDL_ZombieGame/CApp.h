//==============================================================================
// Zombie Game - Based on SDL API
// Ricardo Lodi
//==============================================================================
#ifndef _CAPP_H_
#define _CAPP_H_

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include <time.h>
#include <string>


#include <SDL.h>
#include <SDL_ttf.h>			//for fonts
#include <SDL_mixer.h>          //for sound and music


#include "CPlayer.h"
#include "CScroll_Player.h"
#include "CSpriteSheet.h"
#include "mywindow.h"


#define TICK_INTERVAL       10
#define NUM_ZOMBIES         10
#define NUM_CANOES			10
#define MAX_SPEED           1

//====================================================================================================
//Class CApp works as Game Manager for the game. It will control the game mechanics, players, font, etc.
class CApp
{
private:
	bool Running;
	bool onCanoe = false;
	bool gameWin = false;
	int canoeNumber = -1;
	TTF_Font * font;					// Pointer to font, stores the type and size of the font
	TTF_Font * font1;					

	SDL_Color color;					// Text Color
	SDL_Color color1;					// Text Color

	char message[100];					// Message String so we can display it

	SDL_Surface * messageSurface;		// Pointer to the Surface where we display the message
	SDL_Texture * messageTexture;		// Pointer to the texture, converts the surface to texture
	SDL_Rect messageRect;				// Location

	//The music that will be played
	Mix_Music *gMusic = NULL;

	//Sound effects that will be used
	Mix_Chunk *gScratch = NULL;

	Uint32 next_time;
	SDL_Window *window;
	SDL_Renderer *renderer;

	CSpriteSheet zombie[NUM_ZOMBIES];
		
	CPlayer	canoe[NUM_CANOES];

	CScroll_Player background = CScroll_Player(0, 0, window_w, window_h/3);
	CScroll_Player grass = CScroll_Player(0, 0, window_w, window_h);
	CScroll_Player safeGround = CScroll_Player(0, 0, window_w, 90);

	CSpriteSheet Player;
	SDL_Rect runnerspot;				// SDL_Rect for spritesheet
	SDL_Rect zLocation[NUM_ZOMBIES];

	int live, score;					// Variables to Store number of lives and score
	int grassStart = 300;

public:
	CApp();
	Uint32 time_left(void);
	int OnExecute();

public:
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnLoop();
	void OnRender();
	void OnCleanup();

	bool loadMedia();
	bool check_collision(SDL_Rect A, SDL_Rect B);
	void displayGameStats(int x, int y, const char* formattedString, int number);
	void displayGameOver(int x, int y, const char* formattedString);

	int LoadSprite(const char *file, SDL_Texture **psprite, SDL_Rect *prect);
	void MoveSprites();
		
	//Canoe
	void StartCanoes();
	//safe ground
	void StartGrounds();
		
};

//==============================================================================

#endif
