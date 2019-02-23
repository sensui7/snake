#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>
#include <string>
#include "textureloader.hpp"
#include "snake.hpp"
#include "food.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using snakePtr = std::shared_ptr<Snake>;
using foodPtr = std::shared_ptr<Food>;

struct state
{
	SDL_Texture* snakeTexture;
	SDL_Texture* foodTexture;
};

class Game 
{
	public:
		Game();
		~Game();

		bool init();
		void processInput();
		void update();
		void render();
		void close();

		bool running() { return _isRunning; }

	private:
		bool _isRunning;
		SDL_Renderer* _renderer;
		SDL_Window* _window;

		// Game objects
		snakePtr _snake;
		foodPtr _food;
		state gameState;

		void error(std::string);
};

#endif

