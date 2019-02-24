/*
	Steven Tran
	CS410: C++
	Final Project
*/

#ifndef SNAKE
#define SNAKE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <list>

const int DEFAULT_WIDTH = 20;
const int DEFAULT_HEIGHT = 20;

enum dir 
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct snakeParts
{
	SDL_Rect part;
	dir direction;
};

/*
	This class manages the position and size of the snake.
	A list (linear-linked list) is used to manage the body
	of the snake.
*/
class Snake
{
	public:
		Snake(int32_t pX, int32_t pY);
		~Snake();

		SDL_Rect& getHead();
		std::list<snakeParts>& getAll();

		bool checkSelfCollision();
		dir getCurrDir();
		void setDir(dir d);
		void move();
		void grow();
		void restart();
			
	private:
		std::list<snakeParts> _body;
};

#endif

