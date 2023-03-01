#ifndef CSCROLL_PLAYER_H
#define CSCROLL_PLAYER_H

#include "CApp.h"

//Class created to handle background images

class CScroll_Player : public CPlayer
{
public:
    int scroll = 0;	

    CScroll_Player();
    CScroll_Player(int sx, int sy, int sw, int sh);
    virtual ~CScroll_Player();
        
    SDL_Rect destscr;
    SDL_Rect src;											// Where to get Image (Part of Big Image)
        
    void display(SDL_Renderer *prenderer);
    int loadPlayer(SDL_Renderer *prenderer);
    int loadPlayer(SDL_Renderer* prenderer, bool safe);
        
    void move();
    
protected:
private:
};

#endif // CSCROLL_PLAYER_H
