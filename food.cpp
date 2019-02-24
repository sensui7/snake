#include "food.hpp"

Food::Food(int32_t pX, int32_t pY)
{
	_food.x = pX;
	_food.y = pY;
	_food.w = 20;
	_food.h = 20;
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
	auto newX = (rand() % 800);
	auto newY = (rand() % 500);

	_food.x = roundToNearestMultiple20(newX, 800);
	_food.y = roundToNearestMultiple20(newY, 500);
}

SDL_Rect& Food::getFood()
{
	return _food;
}

void Food::restart()
{
	_food.x = 200;
	_food.y = 300;
}
