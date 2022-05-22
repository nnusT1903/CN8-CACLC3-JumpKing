#pragma once
#ifndef GAME_H
#define GAME_H

#include "Header.h"
#include <iostream>
#include "textObj.h"
#include <fstream>

static const int SCREEN_WIDTH = 960;
static const int SCREEN_HEIGHT = 720;

static const int TILE_WIDTH = 16;
static const int TILE_HEIGHT = 16;
static const int TILE_NUMBERS = 3;

static const int LEVEL_WIDTH = 960;
static const int LEVEL_HEIGHT = 3840;


class Game
{
private:
    int count = 0;
    bool isRunning;
    bool win;
    bool isRetrying;
    SDL_Window* window = NULL;

public:
    Game();
    ~Game();

    int createMenu(TTF_Font* font);
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void retry();
    void clean();

    bool checkSelected(const int& x, const int& y, const SDL_Rect& rect);
    bool running(); 
    bool winning(); 
    bool retrying(); 
    

    static SDL_Renderer* renderer;

};
#endif
