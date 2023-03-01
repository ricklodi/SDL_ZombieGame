#ifndef CPLAYER_H
#define CPLAYER_H

#include "CApp.h"

class CPlayer
{
public:
    bool loaded;

    SDL_Rect position;
    SDL_Rect velocity;

    char imagename[255];

    CPlayer(const char image[]="",int x=0, int y=0, int vx=0, int vy=0)
    {
        strncpy_s(imagename,image,255);
        position.x = x;
        position.y = y;
        velocity.x = vx;
        velocity.y = vy;
        loaded = false;
    }

    int loadPlayer(SDL_Renderer *prenderer);
    void display(SDL_Renderer *prenderer);
    void move();
    void setImage();


protected:
    SDL_Texture *texture;
};

#endif
