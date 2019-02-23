#ifndef GAME
#define GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Game 
{
	public:
		Game();
		~Game();

		bool init();
		void handleEvents();
		void update();
		void render();
		void close();

		bool running() { return _isRunning; }
	private:
		bool _isRunning;
		SDL_Renderer* _renderer;
		SDL_Window* _window;

		void error(std::string);
};

#endif

