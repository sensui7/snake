/*
	Steven Tran
	CS410
	Final Project
*/

#ifndef FOOD
#define FOOD

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <iostream>

const int DEFAULT_FOOD_WIDTH = 20;
const int DEFAULT_FOOD_HEIGHT = 20;
const int DEFAULT_FOOD_POSX = 200;
const int DEFAULT_FOOD_POSY = 300;
const int GAME_WINDOWX = 800;
const int GAME_WINDOWY = 500;

class Food
{
	public:
		Food(int32_t pX, int32_t pY);
		~Food();

		int roundToNearestMultiple20(int n, int limit);
		SDL_Rect& getFood();
		void newLocation();
		void restart();

	private:
		SDL_Rect _food;	
};

#endif

