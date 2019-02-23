#ifndef SNAKE
#define SNAKE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <list>

const int DEFAULT_WIDTH = 20;
const int DEFAULT_HEIGHT = 20;

enum dir {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Snake
{
	public:
		Snake(int32_t pX, int32_t pY) : _direction(RIGHT)
		{
			_rect.w = DEFAULT_WIDTH;
			_rect.h = DEFAULT_HEIGHT;
			_rect.x = pX;
			_rect.y = pY;

			_body.push_front(_rect);
		}

		~Snake() {}

		SDL_Rect& getRect() { return _rect; }

		void setDir(uint32_t d) { _direction = d; }

		void move()
		{
			switch(_direction)
			{
				case UP:
					_rect.y -= 4;
					break;
				case DOWN:
					_rect.y += 4;
					break;
				case LEFT:
					_rect.x -= 4;
					break;
				case RIGHT:
					_rect.x += 4;
					break;
			}
		}
			
	private:
		uint32_t _direction;	
		SDL_Rect _rect;
		std::list<SDL_Rect> _body;
};

#endif

