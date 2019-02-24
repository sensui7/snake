/*
	Steven Tran
	CS410
	Final Project
*/

#include "game.hpp"
#include <iostream>
#include <memory>

using gamePtr = std::shared_ptr<Game>;

// Capping the frames per second
const int FPS = 30;
const int frameDelay = 1000 / FPS;

// Reference: http://gameprogrammingpatterns.com/game-loop.html
int main (int argc, char * argv[]) 
{
	gamePtr game = std::make_shared<Game>();
	game -> init();

	uint32_t frameStart = 0, frameEnd = 0, frameDuration = 0;

	while (game -> running())
	{
		frameStart = SDL_GetTicks();
		game -> processInput();
		game -> update();
		game -> render();
		frameEnd = SDL_GetTicks();

		// Delay the difference to get 30 FPS
		// Each frame is expected to run ~33.33 ms and not any faster 
		frameDuration = frameEnd - frameStart;
		if (frameDelay > frameDuration)
		{
			SDL_Delay(frameDelay - frameDuration);
		}
	}

	game -> close();

	return 0;
}
