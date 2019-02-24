#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>
#include <string>
#include "textureloader.hpp"
#include "snake.hpp"
#include "food.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;

// Offset used to position game over text in center
const int TEXT_W_OFFSET = 100;
const int TEXT_H_OFFSET = 25;

using snakePtr = std::shared_ptr<Snake>;
using foodPtr = std::shared_ptr<Food>;

struct state
{
	SDL_Texture* snakeTexture;
	SDL_Texture* foodTexture;
	SDL_Texture* ttfTexture;
	bool gameOver;
};

/*
	This class manages the user input, update, and rendering.
	It also manages the game objects: snake and food.
*/
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
		TTF_Font* _font;

		state gameState;
		snakePtr _snake;
		foodPtr _food;

		void error(std::string);
		void errorTTF(std::string);
};

#endif

