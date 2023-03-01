//==============================================================================
#include "CApp.h"

void CApp::OnRender()
{
    /* Update the screen! */
    SDL_RenderPresent(renderer);
    SDL_Delay(time_left());
    next_time += TICK_INTERVAL;
}