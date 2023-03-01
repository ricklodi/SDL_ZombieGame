#ifndef CSPRITESHEET_H
#define CSPRITESHEET_H

#define MAX_SPRITE_IMAGES 20

#include"CApp.h"


class CSpriteSheet 
{
public:
    char fname[255];

    int max_images;
    int cur_image = 0;
    int w_width;    // Whole width and height of texture
    int w_height;
        
    SDL_Rect images[MAX_SPRITE_IMAGES];
    SDL_Rect runnerspot;        // spritesheet

    //for zombies only
    SDL_Rect position;
    SDL_Rect velocity;
        
    CSpriteSheet();
        
    virtual ~CSpriteSheet();
        
    void set_sheet(const char n[]) { strncpy_s(fname,n,255); }
        
    int load_sheet(SDL_Renderer *renderer);
        
    void config_sheet(int num_of_images, int sx, int sy, int sw, int sh, int wx, int hy, int border);
    void play(SDL_Renderer *r, SDL_Rect *pos, bool gotonext);
    void rewind() {  cur_image = 0; }
    void move();

    //Functions for the ZOMBIE only
    void move(SDL_Rect &pos, bool isZombie);
    void Direction(char direct);
    void display(SDL_Renderer* prenderer);
    int loadPlayer(SDL_Renderer* renderer, SDL_Rect* post, bool isZombie);

protected:

private:
    SDL_Texture *texture;
    SDL_Surface *ps;
};

#endif // CSPRITESHEET_H
