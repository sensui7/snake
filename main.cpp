#include "game.hpp"
#include <iostream>
#include <memory>

// Type alias (c++11)
using gamePtr = std::shared_ptr<Game>;

int main (int argc, char * argv[]) 
{
	gamePtr game = std::make_shared<Game>();
	game -> init();

	while (game -> running())
	{
		game -> handleEvents();
		game -> handleEvents();
		game -> handleEvents();
	}

	std::cout << "Hello World! This is a testing message.\n";
	return 0;
}
