#ifndef FOOD
#define FOOD

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Food
{
	public:
		Food(int32_t pX, int32_t pY) 
		{
			_food.x = pX;
			_food.y = pY;
			_food.w = DEFAULT_WIDTH;
			_food.h = DEFAULT_HEIGHT;
		}

		SDL_Rect& getRect()
		{
			return _food;
		}

		~Food() {}

	private:
		SDL_Rect _food;	
};

#endif

