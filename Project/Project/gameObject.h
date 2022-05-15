#pragma once
#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Game.h"
#include <math.h>
#include "header.h"

#define gravity 0.8
#define MAX_FALL_SPEED 20

using namespace std;

enum condition { standing, running, charging, jumping };
typedef struct {
    int left;
    int right;
    int up;
    int jump;
}
Input;





class GameObject
{
private:

    double xpos;
    double ypos;

    double xvel;
    double yvel;

    int frame;

    Uint32 startTime;
    int jumpTime;

    SDL_Texture* objTextureRight = NULL;
    SDL_Texture* objTextureLeft = NULL;
    SDL_Rect srcRect, destRect, collider;

    Mix_Chunk* High = NULL;

    SDL_Rect RunningRight[5];
    SDL_Rect RunningLeft[5];

    condition status;
    Input inputType;
    bool onGround;
    bool isWin;

public:
    GameObject(int x, int y);
    ~GameObject();

    friend void Game::handleEvents();
    friend void Game::update();
    friend void Game::retry();

    SDL_Rect GetCollider() { return collider; }

    void Update(SDL_Rect Tile[][60], int Mapping[][60]);

    void RunLeft();
    void RunRight();

    void PrepareJump();
    void Jump();
    void JumpLeft();
    void JumpRight();


    void StopRunRight();
    void StopRunLeft();
    void StopRunUp();
    void StopRunDown();

    void Reset();

    void SetClips();
    void Render();
    void ObjectClose();

    void CollideVertical(SDL_Rect& col, SDL_Rect Tile[][60], int Mapping[][60]);
    void CollideHorizontal(SDL_Rect& col, SDL_Rect Tile[][60], int Mapping[][60]);
    bool checkCollision2(SDL_Rect a, SDL_Rect b);

    void CalculateAngle();

    int Getxspeed() { return xspeed; }
    int Getxvel() { return (int)xvel; }
    int Getyvel() { return (int)yvel; }


    static const int xspeed = 1;
    static const int yspeed = 1;

    int maxxspeed = 6;
    int maxyspeed = 8;


    static const int KING_WIDTH = 48;
    static const int KING_HEIGHT = 48;

    SDL_Rect Camera = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

    bool isSpdBuff, isJmpBuff, isLag;
};
#endif