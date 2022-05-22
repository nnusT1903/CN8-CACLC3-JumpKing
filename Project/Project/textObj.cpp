#include "textObj.h"

textObj::textObj()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
}

textObj::~textObj()
{
	free();
}



bool textObj::loadFromRenderedText(TTF_Font* font, SDL_Renderer* screen)
{

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, strVal.c_str(), textColor);
	if (textSurface)
	{	
		mTexture = SDL_CreateTextureFromSurface(screen, textSurface);
		mWidth = textSurface->w;
		mHeight = textSurface->h;
		SDL_FreeSurface(textSurface);
	}
	

	return mTexture != NULL;
}

void textObj::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}


void textObj::renderText(SDL_Renderer* screen, int x, int y,
	SDL_Rect* clip, double angle, SDL_Point* center,
	SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, mTexture, clip, &renderQuad, angle, center, flip);
}

void textObj::setTextColor(const int& color){
	switch (color){
		case white:
			textColor = {255, 255, 255};
			break;
		case black:
			textColor = {0, 0, 0};
			break;
		case red:
			textColor = {255, 0, 0};
			break;
		case yellow:
			textColor = {255, 255, 0};
			break;
		case green:
			textColor = {0, 255, 0};
			break;
		case blue:
			textColor = {0, 0, 255};
			break;
		default:
			textColor = {255, 255, 255};
			break;
	}
}
