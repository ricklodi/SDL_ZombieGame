//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {

    switch(Event->type)
    {
		case SDL_QUIT:

            Running = false;
            break;

        case SDL_KEYDOWN:

            switch(Event->key.keysym.sym)
            {
				// UP Arrow key
                case SDLK_UP:
                    Player.Direction('U');
					runnerspot.y -= 10;								// change the y location by -10
                    if (runnerspot.y < 0)
                    {
						runnerspot.y = 0;
                    }
                    break;

				// DOWN Arrow key
				case SDLK_DOWN:
                    Player.Direction('D');
                    runnerspot.y += 10;								// change the y location by +10
                    if (runnerspot.y >= (window_h - runnerspot.h))
                    {
						runnerspot.y = (window_h - runnerspot.h);
					}
					break;

				// LEFT Arrow key
				case SDLK_LEFT:
                    Player.Direction('L');
					runnerspot.x -= 10;								// change the x location by -10
                    if (runnerspot.x < 0)
                    {
						runnerspot.x = 0;
                    }
                    break;

				// RIGHT Arrow key
                case SDLK_RIGHT:
                    Player.Direction('R');
                    runnerspot.x += 10;								// change the x location by +10
                    if (runnerspot.x >= (window_w - runnerspot.w))
                    {
						runnerspot.x = (window_w - runnerspot.w);
                    }
                    break;

				// When a is pressed speed of arrows falling down and scrolling background is increased by 1
                case SDLK_a:
					background.velocity.x+=1;
                    for(int i = 0; i < NUM_ZOMBIES ; ++i)
					{
                            zombie[i].velocity.y += 1;
                    }
                    break;

				// When z is pressed speed of arrows falling down and scrolling background is decreased by 1
				case SDLK_z:
					if (background.velocity.x > 0)
					{
						background.velocity.x--;	
					}

					for(int i = 0 ; i < NUM_ZOMBIES ; ++i)
					{
                            zombie[i].velocity.y -= 1;
                    }
                             break;
				// 'p' To play the Game again
                case SDLK_p:
					SDL_DestroyRenderer( renderer );
                    SDL_DestroyWindow( window );
                    window = NULL;
                    renderer = NULL;
                    SDL_QUIT;

                    OnInit();
                    break;
				
				// 'Esc' to exit 
                case SDLK_ESCAPE:

                    Running=false;
                    break;
            }
    }
}

//==============================================================================
