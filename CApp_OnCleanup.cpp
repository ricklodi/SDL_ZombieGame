//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnCleanup() 
{
    SDL_DestroyTexture(messageTexture);			//Release the Texture and Surfaces
    SDL_FreeSurface(messageSurface);
    TTF_CloseFont(font);						//Release the font
    TTF_Quit(); 								//Shuts down the SDL_ttf subsystem

    //Free the sound effects
    Mix_FreeChunk( gScratch );
    gScratch = NULL;

    //Free the music
    Mix_FreeMusic( gMusic );
    gMusic = NULL;

    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    Mix_Quit();
    
	//IMG_Quit();
    SDL_Quit();

}

//==============================================================================
