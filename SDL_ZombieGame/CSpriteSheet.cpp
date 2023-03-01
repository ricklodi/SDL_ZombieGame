#include "CApp.h"

CSpriteSheet::CSpriteSheet()
{
    cur_image = 0;
}

CSpriteSheet::~CSpriteSheet()
{
}


int CSpriteSheet::load_sheet(SDL_Renderer *renderer)
{
    SDL_Surface *temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(fname);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", fname, SDL_GetError());
        return (-1);
    }
    w_width = temp->w;
    w_height = temp->h;

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8 *) temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint16 *) temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16 *) temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                            (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32 *) temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }
    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return (0);
}

    //int num_of_images    // How many images to extract from texture
    // int sx,             // Start image x loc in texture
    //  int sy,            // Start image y loc in texture
    //   int sw,           // Width of ONE image in texture
    //    int sh,          // Height of ONE image in texture
    //     int wx,         // How many images on ONE row
    //      int hy,        // How many rows of images on texture
    //       int border    // How many pixels between images

    //Note: Images are not really extracted... locations are saved to allow quick display...


void CSpriteSheet::config_sheet(int num_of_images, int sx, int sy, int sw, int sh, int wx, int hy, int border) //4, 10 16 27 49 4 1 20
{
    SDL_Rect *pr;
    int curx,cury;
    int working_rec = 0;
    int working_row = 1;
    int working_col = 1;

    curx = sx;
    cury = sy;
    while (working_rec < num_of_images && working_row <= hy)
    {
        pr = &images[working_rec];
        pr->x = curx;
        pr->y = cury;
        pr->w = sw;
        pr->h = sh;
        
        working_col++;
        working_rec++;
        
        curx += sw + border;
        if (working_col>wx)
        {
            working_row++;
            working_col = 1;
            cury += sh + border;
            curx = sx;
        }
        
    }
    max_images = num_of_images;

}

/*
    Display the Sprite (current position) to the screen
    and optionally move to next image....

*/
void CSpriteSheet::play(SDL_Renderer *r, SDL_Rect *pos, bool gotonext)
{
    SDL_RenderCopy(r,texture,&images[cur_image],pos);
    if (gotonext)
    {
        cur_image++;
        if (cur_image>=max_images)
            cur_image = 0;
    }
}

void CSpriteSheet::move()
{
    SDL_Rect *r;

    r = &runnerspot;

	/*|| (r->x >= (window_w - r->w))*/
    if ((r->x < 0) )
    {
        r->x = 0;
    }

    if ((r->y < 0) || (r->y >= (window_h - r->h)))
    {
        r->y = r->y;
    }
}

void CSpriteSheet::Direction(char direct)
{
    switch (direct){
    
        case 'D':
            config_sheet(4, 10, 16, 27, 49, 4, 1, 22);
            break;
        case 'U':
            config_sheet(4, 10, 208, 27, 49, 4, 1, 22);
            break;
        case 'L':
            config_sheet(4, 10, 82, 27, 49, 4, 1, 22);
            break;
        case 'R':
            config_sheet(4, 10, 146, 27, 49, 4, 1, 22);
            break;
    }
}

//Added to move the zombie

void CSpriteSheet::move(SDL_Rect &pos, bool isZombie)
{
    SDL_Rect* p;
    SDL_Rect* v;

    p = &pos;
    v = &velocity;

    p->x += v->x;
    if ((p->x < 0) || (p->x >= (window_w - images[0].w)))
    {
        v->x = -v->x;
        p->x += v->x;
    }
    p->y += v->y;
    if ((p->y < 0) || (p->y >= (window_h - images[0].h)))
    {
        v->y = -v->y;
        p->y += v->y;
    }

}



void CSpriteSheet::display(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, &position);
}

int CSpriteSheet::loadPlayer(SDL_Renderer* renderer, SDL_Rect* post , bool isZombie)
{
    SDL_Surface* temp;

    /* Load the sprite image */
    temp = SDL_LoadBMP(fname);
    if (temp == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s", fname, SDL_GetError());
        return (-1);
    }
    post->w = temp->w;
    post->h = temp->h;

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette)
    {
        SDL_SetColorKey(temp, SDL_TRUE, *(Uint8*)temp->pixels);
    }
    else
    {
        switch (temp->format->BitsPerPixel)
        {
        case 15:
            SDL_SetColorKey(temp, SDL_TRUE,
                (*(Uint16*)temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint16*)temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, SDL_TRUE,
                (*(Uint32*)temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, SDL_TRUE, *(Uint32*)temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    if (!texture)
    {
        fprintf(stderr, "Couldn't create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(temp);
        return (-1);
    }
    SDL_FreeSurface(temp);

    /* Game is ready! */
    return (0);
}