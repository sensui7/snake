#include "game.hpp"

Game::Game()
{

}

Game::~Game()
{

}

void Game::error(std::string errorMsg)
{
	std::cout << errorMsg << " SDL Error: " << SDL_GetError() << "\n";	
}

bool Game::init()
{
	bool success = true;

	// Initialize subsystem(s)
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		error("SDL couldn't be initialized!");
		return !success;
	}

	// Create window
	_window = SDL_CreateWindow("Snake", 
							   SDL_WINDOWPOS_UNDEFINED, 
							   SDL_WINDOWPOS_UNDEFINED,
							   SCREEN_WIDTH,
							   SCREEN_HEIGHT,
							   SDL_WINDOW_SHOWN);
	if (_window == nullptr) 
	{
		error("Window couldn't be created!");
		return !success;
	}

	// Create vsynced renderer for window
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_renderer == nullptr)
	{
		error("Renderer couldn't be created!");
		return !success;
	}

	SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0xff);

	_isRunning = true;

	return success;
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type)
	{
		case SDL_QUIT:
			_isRunning = false;
			break;
		default:
			break;
	}
}

void Game::update()
{

}

// Reference: https://wiki.libsdl.org/SDL_RenderPresent
void Game::render()
{
	// Clear current rendering target with drawing color
	SDL_RenderClear(_renderer);
	// Update screen with any rendering performed since previous call
	SDL_RenderPresent(_renderer);
}

void Game::close()
{
	SDL_DestroyWindow(_window);
	_window = nullptr;
	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}
