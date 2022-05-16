#pragma once
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
class Timer
{
public:
	Timer() { start = 0; }
	~Timer(){}
	void setTime();
	void reset();
	int getTimeElapsed();

private:
	int start;
};


#endif