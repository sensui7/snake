/*
	Steven Tran
	CS410
	Final Project
*/

#include "snake.hpp"

Snake::Snake(int32_t pX, int32_t pY)
{
	SDL_Rect tmp;
	tmp.w = DEFAULT_SNAKE_WIDTH;
	tmp.h = DEFAULT_SNAKE_HEIGHT;
	tmp.x = pX;
	tmp.y = pY;

	snakeParts sp;
	sp.part = tmp;
	sp.direction = RIGHT;
	_body.push_front(sp);
}

Snake::~Snake() {}

SDL_Rect& Snake::getHead() { return _body.front().part; }

std::list<snakeParts>& Snake::getAll() { return _body; }

void Snake::setDir(dir d)
{ 
	auto it = _body.begin();
	(*it).direction = d;
}

dir Snake::getCurrDir()
{
	return _body.front().direction;
}

/*
The movement can be described as below:
e.g. (0, 60), (0, DEFAULT_SNAKE_POS), (0, SNAKE_MOVE_DISTANCE) w/ RIGHT direction
	 ^head			   ^tail

Another movement to the right (0, 80) will result in
 (0, 80), (0, 60), (0, DEFAULT_SNAKE_POS) w/ RIGHT direction
 ^ head			   ^tail
*/
void Snake::move()
{
	snakeParts tmp = _body.front();
	SDL_Rect head = tmp.part;
	dir direction = tmp.direction;

	switch(direction)
	{
		case UP:
				head.y = (head.y < 0) ? head.y + DEFAULT_SCREEN_HEIGHT : (head.y - SNAKE_MOVE_DISTANCE) % DEFAULT_SCREEN_HEIGHT;
			break;
		case DOWN:
				head.y = (head.y + SNAKE_MOVE_DISTANCE) % DEFAULT_SCREEN_HEIGHT;
			break;
		case LEFT:
				head.x = (head.x < 0) ? head.x + DEFAULT_SCREEN_WIDTH : (head.x - SNAKE_MOVE_DISTANCE) % DEFAULT_SCREEN_WIDTH;
			break;
		case RIGHT:
				head.x = (head.x + SNAKE_MOVE_DISTANCE) % DEFAULT_SCREEN_WIDTH;
			break;
	}

	std::list<snakeParts> newBody(_body.begin(), std::prev(_body.end(), 1));
	snakeParts sp;
	sp.part = head;
	sp.direction = direction; 
	newBody.push_front(sp);
	_body = newBody;
}


// Growing means take the copy of the tail (last part)
// and then attach a new part behind it. Since this comes
// after the call to move in Game::update(), the snake
// is one part ahead w.r.t. to the current direction.
// Thus, the copy of the tail is the previous snapshot
// (one block before).
void Snake::grow()
{
	auto snakeTail = _body.back();
	SDL_Rect tail = snakeTail.part;
	dir direction = snakeTail.direction;

	switch(direction)
	{
		case UP:
				tail.y = (tail.y < 0) ? tail.y + DEFAULT_SCREEN_HEIGHT : (tail.y + SNAKE_MOVE_DISTANCE) % DEFAULT_SCREEN_HEIGHT;
			break;
		case DOWN:
				tail.y = (tail.y - SNAKE_MOVE_DISTANCE) % DEFAULT_SCREEN_HEIGHT;
			break;
		case LEFT:
				tail.x = (tail.x < 0) ? tail.x + DEFAULT_SCREEN_WIDTH : (tail.x + SNAKE_MOVE_DISTANCE) % DEFAULT_SCREEN_WIDTH;
			break;
		case RIGHT:
				tail.x = (tail.x - SNAKE_MOVE_DISTANCE) % DEFAULT_SCREEN_WIDTH;
	}

	snakeParts sp;
	sp.part = tail;
	sp.direction = direction; 

	_body.push_back(sp);
}


// If the head matches some part of the body, it's collided
bool Snake::checkSelfCollision()
{
	auto it = std::next(_body.cbegin(), 1);
	SDL_Rect head = _body.front().part, tmp;

	for (; it != _body.cend(); ++it)
	{
		tmp = (*it).part;

		if (tmp.x == head.x && tmp.y == head.y)
		{
			return true;
		}
	}

	return false;
}

void Snake::restart()
{
	Snake newSnake(DEFAULT_SNAKE_POS, DEFAULT_SNAKE_POS);
	*this = newSnake;
}
