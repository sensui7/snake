#include "snake.hpp"

Snake::Snake(int32_t pX, int32_t pY)
{
	SDL_Rect tmp;
	tmp.w = DEFAULT_WIDTH;
	tmp.h = DEFAULT_HEIGHT;
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
e.g. (0, 60), (0, 40), (0, 20) w/ RIGHT direction
	 ^head			   ^tail

Another movement to the right (0, 80) will result in
 (0, 80), (0, 60), (0, 40) w/ RIGHT direction
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
				head.y = (head.y < 0) ? head.y + 500 : (head.y - 20) % 500;
			break;
		case DOWN:
				head.y = (head.y + 20) % 500;
			break;
		case LEFT:
				head.x = (head.x < 0) ? head.x + 800 : (head.x - 20) % 800;
			break;
		case RIGHT:
				head.x = (head.x + 20) % 800;
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
// Thus, the copy of the tail is the previous snapshot.
void Snake::grow()
{
	auto snakeTail = _body.back();
	SDL_Rect tail = snakeTail.part;
	dir direction = snakeTail.direction;

	switch(direction)
	{
		case UP:
				tail.y = (tail.y < 0) ? tail.y + 500 : (tail.y + 20) % 500;
			break;
		case DOWN:
				tail.y = (tail.y - 20) % 500;
			break;
		case LEFT:
				tail.x = (tail.x < 0) ? tail.x + 800 : (tail.x + 20) % 800;
			break;
		case RIGHT:
				tail.x = (tail.x - 20) % 800;
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
	Snake newSnake(40, 40);
	*this = newSnake;
}
