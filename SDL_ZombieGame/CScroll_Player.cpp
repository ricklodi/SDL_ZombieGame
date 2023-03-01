#include "CApp.h"

CScroll_Player::CScroll_Player()
{
    
}

CScroll_Player::CScroll_Player(int sx, int sy, int sw, int sh)
{
    src.x = sx;
    src.y = sy;
    src.w = sw,
    src.h = sh;
}

CScroll_Player::~CScroll_Player()
{

}


void CScroll_Player::display(SDL_Renderer *prenderer)
{
    SDL_RenderCopy(prenderer, texture, &src, &destscr);
}

int CScroll_Player::loadPlayer(SDL_Renderer *prenderer)
{
    int retval;

    retval = CPlayer::loadPlayer(prenderer);
    destscr.x = 0;
    destscr.y = 0;
    destscr.h = window_h;
    destscr.w = window_w;
    velocity.x = 0; //changed velocity from 1 to zero
    velocity.y = 0;
    return (retval);
}

int CScroll_Player::loadPlayer(SDL_Renderer* prenderer, bool safe)
{
    int retval;

    retval = CPlayer::loadPlayer(prenderer);
    destscr.x = src.x;
    destscr.y = src.y;
    destscr.h = src.h;
    destscr.w = src.w;
    velocity.x = 0; //changed velocity from 1 to zero
    velocity.y = 0;
    return (retval);
}

void CScroll_Player::move()
{
    src.x += velocity.x;
    src.y += velocity.y;

    if (src.x >= position.w - window_w)   // Assuming that the backgound image is greater than window width.
    {
        src.x += velocity.x;
        src.x  = 0 ;
        scroll += 1;
    }

    if (src.x < 0)
    {
        src.x += velocity.x;
        src.x = 0 ;
    }

    //Added Y movement
    if (src.y >= position.h - window_h) 
    {
        src.y += velocity.y;
        src.y = 0;
        scroll += 1;
    }

    if (src.y < 0)
    {
        src.y += velocity.y;
        src.y = 0;
    }
}