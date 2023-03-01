//==============================================================================
#include "CApp.h"

//==============================================================================
bool CApp::OnInit()
{

    int i;

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK)<0)
    {
        return false;
    }

	//TTF Initialization
    TTF_Init( );	

    //Loads font with font size
    font = TTF_OpenFont("lazy2.ttf", 20);
    color = {255,255,255};

    font1 = TTF_OpenFont("three.ttf", 50);
    color1 = {255,245,209};

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        Running = false;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        Running = false;
    }

    //Plays Music in Background while GAMEPLAY
    loadMedia();
    //Mix_PlayMusic( gMusic, -1 );

    window = SDL_CreateWindow("Zombie Game",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (!window)
        return false;
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
        return false;

    srand((unsigned int)time(NULL));

    //Create the zombies
    for (i = 0; i < NUM_ZOMBIES; ++i) {
        zombie[i].set_sheet("zombie.bmp");
        zombie[i].loadPlayer(renderer, &zLocation[i], true);
        zombie[i].velocity.x = rand() % 2 + 1;
        zombie[i].velocity.y = 0;

        //SETTING Zombie direction based on position and velocity
        (zombie[i].velocity.x < 0) ? zombie[i].Direction('L') : zombie[i].Direction('R');

        //SETTING POSITION RANDOMICALLY WITH SPACE EQUALS TO THE IMAGE HEIGHT
        do {
            zombie[i].position.y = rand() % (window_h - zombie[i].images[0].h * 2);
        } while (zombie[i].position.y < grassStart);

        zombie[i].position.x = rand() % (window_w - zombie[i].images[0].w);
        //Assigning the zombie position and height/width from CSPriteSheet to zLocation from CApp
        zLocation[i].h = zombie[i].images[0].h;
        zLocation[i].w = zombie[i].images[0].w;
        zLocation[i].x = zombie[i].position.x;
        zLocation[i].y = zombie[i].position.y;
    }

    //PLAYER sprite sheet declaration
    Player.set_sheet("human.bmp");
    if (Player.load_sheet(renderer) != 0)
    {
        printf("Bad load of runner animation file\n");
    }
    Player.Direction('U');
    runnerspot.h = Player.images[0].h-7;
    runnerspot.w = Player.images[0].w;
    runnerspot.x = window_w / 2;
    runnerspot.y = window_h - Player.images[0].h;

    // Press 'p' to reset lives and score value to default.
    live = 0010;
    score = 0000;

    //Background IMAGE DECLARATION
    strncpy_s(background.imagename,"water.bmp",255);
    background.loadPlayer(renderer);

    //Grass Initialization
    strncpy_s(grass.imagename, "grass.bmp", 255);
    grass.loadPlayer(renderer);
    //Positioning grass to be at the middle of the screen
    grass.destscr.y = grassStart;
    StartCanoes();
    StartGrounds();
    return true;
}

//Initialize the Canoe based on number of canoes
void CApp::StartCanoes()
{
    for (int i = 0; i < NUM_CANOES; ++i) 
    {      
        strncpy_s(canoe[i].imagename, "canoe.bmp", 255);
        canoe[i].loadPlayer(renderer);
        static Uint32 posBump = canoe[i].position.w;
        canoe[i].velocity.x = rand() % 2 + 1;
        canoe[i].velocity.y = 0;
        canoe[i].position.x = rand() % (window_w - canoe[i].position.w);
        canoe[i].position.y = posBump;//rand() % (grassStart);
        posBump += canoe[i].position.h;
        if (posBump > grassStart)
            posBump = canoe[i].position.w;
    }
}

void CApp::StartGrounds()
{
    //safe Ground image is 720x90.
    safeGround.src.x = 0;
    safeGround.src.y = 0;
    safeGround.src.w = window_w;
    safeGround.src.h = 90;
    safeGround.destscr.x = 0;
    safeGround.destscr.y = 0;
    safeGround.destscr.w = window_w;
    safeGround.destscr.h = 90;
    strncpy_s(safeGround.imagename, "safeGround.bmp", 255);
    safeGround.CPlayer::loadPlayer(renderer);
}