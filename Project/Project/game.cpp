#include "Game.h"
#include "texture.h"
#include "GameObject.h"
#include "Map.h"



using namespace std;

SDL_Texture* background = NULL;
SDL_Texture* foreground = NULL;
SDL_Texture* victory = NULL;
SDL_Texture* babe = NULL;
SDL_Texture* spdPot = NULL;
SDL_Texture* jmpPot = NULL;
SDL_Texture* lagPot = NULL;
SDL_Texture* godPot = NULL; // erase lag effect
Mix_Music* Music = NULL;


SDL_Rect spdSrcRect = { 0,0,32,32 };
SDL_Rect spdRect = { 896,3456,32,32 };
SDL_Rect spdDestRect = { 896,3456,32,32 };

SDL_Rect jmpSrcRect = { 0,0,32,32 };
SDL_Rect jmpRect = { 272,1328,32,32};
SDL_Rect jmpDestRect = { 272,1328,32,32};

SDL_Rect lagSrcRect = { 0,0,32,32 };
SDL_Rect lagRect = {288,2576,32,32};
SDL_Rect lagDestRect = {288,2576,32,32};

SDL_Rect godSrcRect = { 0,0,32,32 };
SDL_Rect godRect = {32,1792,32,32};
SDL_Rect godDestRect = {32,1792,32,32};

SDL_Rect babeSrcRect = { 0,0,48,48 };
SDL_Rect babeRect = { 592,112,48,48 };
SDL_Rect babeDestRect = { 592,112,48,48 };



SDL_Rect BgSrc = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, BgDest = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
GameObject* player;
Map* mapper;



SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flag = 0;
    if (fullscreen)
    {
        flag = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Initialized..." << endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
        if (window)
        {
            cout << "Window created!" << endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer created!" << endl;
        }
        isRunning = true;
    }
    else {
        isRunning = false;
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    Music = Mix_LoadMUS("sound/win.wav");

    win = false;
    isRetrying = true;

    background = texture::LoadTexture("image/main_image/background.png");
    foreground = texture::LoadTexture("image/main_image/foreground.png");
    spdPot = texture::LoadTexture("image/speed_pot.png");
    jmpPot = texture::LoadTexture("image/jump_pot.png");
    lagPot = texture::LoadTexture("image/lag_pot.png");
    godPot = texture::LoadTexture("image/god_pot.png"); 
    babe = texture::LoadTexture("image/babe.png");
    victory = texture::LoadTexture("image/victory.png");

    //Icon loading.
    string icoName = "image/icon.bmp";
    SDL_Surface* loadedSurface = SDL_LoadBMP(icoName.c_str());
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));
    SDL_SetWindowIcon(window, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    player = new GameObject(64, LEVEL_HEIGHT - 100);
    mapper = new Map();
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
    {
        isRunning = false;
    }
    else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
            //if(player->onGround == true)
            {
        case SDLK_RIGHT:
        {
            player->inputType.right = 1;
            player->inputType.left = 0;
            break;
        }
        case SDLK_LEFT:
        {
            player->inputType.left = 1;
            player->inputType.right = 0;
            break;
        }
        case SDLK_UP:
        {
            player->inputType.up = 1;
            break;
        }

        case SDLK_SPACE:
            //if(player->status != jumping)
        {
            player->PrepareJump();
            break;
        }
            }
        }
    }
    else if (event.type == SDL_KEYUP)  //&& event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            player->inputType.right = 2;
            break;
        }
        case SDLK_LEFT:
        {
            player->inputType.left = 2;
            break;
        }
        case SDLK_UP:
        {
            player->inputType.up = 2;
            break;
        }
        case SDLK_SPACE:
            //if(player->status != jumping && player->status != charging)
            if (player->onGround == true)
            {
                switch (player->inputType.jump)
                {
                case 0:
                    if (player->isJmpBuff == true)player->JumpBuff();
                    else player->Jump();
                    break;

                case 1:
                    if (player->isJmpBuff == true)player->JumpRightBuff();
                    else player->JumpRight();
                    break;

                case 2:
                    if (player->isJmpBuff == true)player->JumpLeftBuff();
                    else player->JumpLeft();
                    break;
                }
            }
        }
    }
}
void Game::update()
{
    player->Update(mapper->tile, mapper->mapping);
    babeDestRect.y = babeRect.y - player->Camera.y;
    spdDestRect.y = spdRect.y - player->Camera.y;
    jmpDestRect.y = jmpRect.y - player->Camera.y;
    lagDestRect.y = lagRect.y - player->Camera.y;
    godDestRect.y = godRect.y - player->Camera.y;
    if (player->isWin == true)
    {
        win = true;
        if (Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(Music, -1);
        }
    }
    if (player->isWin == false)
    {
        Mix_HaltMusic();
    }
}
void Game::render()
{
    SDL_RenderClear(renderer);
    mapper->DrawMap(player->Camera);
    texture::Draw(background, player->Camera, BgDest);
    // texture::Draw(foreground, player->Camera, BgDest); //for checking the blocks whether they fit or not
    player->Render();
    texture::Draw(foreground, player->Camera, BgDest);
    texture::Draw(babe, babeSrcRect, babeDestRect);
    if(player->isSpdBuff_forDraw == false) texture::Draw(spdPot, spdSrcRect, spdDestRect);
    if(player->isJmpBuff_forDraw == false) texture::Draw(jmpPot, jmpSrcRect, jmpDestRect);
    if(player->isLag_forDraw == false) texture::Draw(lagPot, lagSrcRect, lagDestRect);
    if(player->godPot_draw == false) texture::Draw(godPot, godSrcRect, godDestRect);
    //mapper->DrawMap(player->Camera);

    SDL_RenderPresent(renderer);

}

/// <summary>
/// Retry the Current Level Option?
/// </summary>
void Game::retry()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
    {
        isRunning = false;
    }
    else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_y:
            win = false;
            player->isWin = false;
            isRetrying = true;
            player->Reset();
            break;
        case SDLK_n:
            isRunning = false;
            break;
        }
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, victory, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyTexture(background);
    background = NULL;
    SDL_DestroyTexture(foreground);
    foreground = NULL;
    SDL_DestroyTexture(babe);
    babe = NULL;
    SDL_DestroyTexture(victory);
    victory = NULL;
    SDL_DestroyTexture(spdPot);
    spdPot = NULL;
    SDL_DestroyTexture(jmpPot);
    jmpPot = NULL;
    SDL_DestroyTexture(lagPot);
    lagPot = NULL;
    player->ObjectClose();
    player = NULL;
    mapper->CloseMap();
    mapper = NULL;

    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    cout << "Game cleaned" << endl;
}

bool Game::running()
{
    return isRunning;
}

bool Game::winning()
{
    return win;
}

bool Game::retrying()
{
    return isRetrying;
}

