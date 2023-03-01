//==============================================================================
#include "CApp.h"


using namespace std;

void CApp::MoveSprites()
{
    int i;
    for (i = 0; i < NUM_ZOMBIES; ++i)
    {
        zombie[i].move(zLocation[i], true);
        (zombie[i].velocity.x < 0) ? zombie[i].Direction('L') : zombie[i].Direction('R');
        //IMPLEMENT SPRITSHEET
        static Uint32 zombieCycles[NUM_ZOMBIES] = { 0 };
        if (zombieCycles[i] % 18)
            zombie[i].play(renderer, &zLocation[i], false);
        else
            zombie[i].play(renderer, &zLocation[i], true);
        zombieCycles[i]++;


        if (check_collision(zLocation[i], runnerspot)== true)
        {
            loadMedia();
            Mix_PlayChannel( -1, gScratch, 0 );
            live--;														// decrease life by 1
            score -= 2;													// decrease score by 2
        }
		
        //printf(" LIVES: %d   LEVEL: %d   SCORE: %d   SCROLLS: %d  \r", live, zombie[0].velocity.y, score, background.scroll);
    }


}

//==============================================================================
void CApp::OnLoop()
{
    SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
    SDL_RenderClear(renderer);

    static Uint32 count = 0;

    if ((check_collision(background.src, runnerspot) == true) && (onCanoe == false && gameWin == false))
    {
        live--;
        printf("Collided with the water\n");
    }
;
    background.display(renderer);
    grass.display(renderer);
    MoveSprites();
    
    safeGround.display(renderer);
    if (check_collision(safeGround.src, runnerspot) == true)
    {
        gameWin = true;
    }

    // CANOE MOVEMENT
    for (int i = 0; i < NUM_CANOES; ++i) {
        canoe[i].move();
        canoe[i].display(renderer);
        //Collision between Canoe and the Player
        if (check_collision(canoe[i].position, runnerspot) == true)
        {
            onCanoe = true;
            canoeNumber = i;
            runnerspot.x = canoe[i].position.x + 20;
            runnerspot.y = canoe[i].position.y;
            
        }
        //Confirming that the player is still on the assigned canoe
        if (check_collision(canoe[canoeNumber].position, runnerspot)==false)
        {
            onCanoe = false;
        }  
    }

    //count = player velocity
    if (count % 15)
        Player.play(renderer,&runnerspot,false);
    else
        Player.play(renderer,&runnerspot,true);
    count++;

    //displayGameStats(25, 25, "Score   : %3d", score); Score will not be used for now
    displayGameStats(25, 20, "Lives : %3d", live);

    if (live <= 0)
    {
        background.velocity.x=0;
        for (int i = 0; i < NUM_ZOMBIES; ++i)
        {
			zombie[i].velocity.y = 0;					// Set the velocity of the arrow sprites to zero
			zLocation[i].y = -500;				// Set the position of the arrow sprites to -500 
													// so that it goes out of scope
        }
                
        displayGameOver(window_w/3, window_h/2, "GAME OVER");
        displayGameStats(window_w/3, window_h/2 + 60, "Press 'P' to Play Again",NULL);
        displayGameStats(window_w/3, window_h/2 + 100, "Press 'ESC' to EXIT",NULL);
        Mix_FreeMusic( gMusic );
        gMusic = NULL;

    }

    if (gameWin == true)
    {
        displayGameOver(window_w / 3, window_h / 2, "YOU WON");
        for (int i = 0; i < NUM_ZOMBIES; ++i)
        {
            zombie[i].velocity.y = 0;					// Set the velocity of the arrow sprites to zero
            zLocation[i].y = -500;				// Set the position of the arrow sprites to -500 
                                                    // so that it goes out of scope
        }
    }

}

//==============================================================================
