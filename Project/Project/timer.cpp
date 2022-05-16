#include "Timer.h"

void Timer::setTime() {
	start = SDL_GetTicks();
}

int Timer::getTimeElapsed() {
	return SDL_GetTicks() - start;
}