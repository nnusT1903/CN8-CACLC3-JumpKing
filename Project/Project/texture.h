#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Header.h"
#include "Game.h"

class texture
{
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};


#endif

