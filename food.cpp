/*
	Steven Tran
	CS410
	Final Project
*/
#include "food.hpp"

Food::Food(int32_t pX, int32_t pY)
{
	_food.x = pX;
	_food.y = pY;
	_food.w = DEFAULT_FOOD_WIDTH;
	_food.h = DEFAULT_FOOD_HEIGHT;
}

Food::~Food() {}

int Food::roundToNearestMultiple20(int n, int limit)
{
	if (n % 20 == 0) return n;

	if ((n+1) % 20 != 0 && (n+1) <= limit) 
	{
		return roundToNearestMultiple20(n + 1, limit);
	} 
	else if ((n-1) % 20 != 0 && (n-1) >= 0) 
	{
		return roundToNearestMultiple20(n - 1, 0);
	}
}

void Food::newLocation()
{
	auto newX = (rand() % GAME_WINDOWX);
	auto newY = (rand() % GAME_WINDOWY);

	_food.x = roundToNearestMultiple20(newX, GAME_WINDOWX);
	_food.y = roundToNearestMultiple20(newY, GAME_WINDOWY);
}

SDL_Rect& Food::getFood()
{
	return _food;
}

void Food::restart()
{
	_food.x = DEFAULT_FOOD_POSX;
	_food.y = DEFAULT_FOOD_POSY;
}
