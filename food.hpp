#ifndef FOOD
#define FOOD

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <iostream>

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

