/*
	Steven Tran
	CS410
	Final Project
*/

#include "game.hpp"

Game::Game() : _isRunning(false), _renderer(nullptr), _window(nullptr), _font(nullptr), _snake(nullptr), _food(nullptr) {}

Game::~Game() 
{ 
	SDL_DestroyTexture(gameState.snakeTexture);
	SDL_DestroyTexture(gameState.foodTexture);
	SDL_DestroyTexture(gameState.ttfTexture);
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
							   SDL_WINDOWPOS_CENTERED, 
							   SDL_WINDOWPOS_CENTERED,
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

	// Set color usedf or drawing operations (Rect, Line, & Clear)
	SDL_SetRenderDrawColor(_renderer, 0xff, 0xff, 0xff, 0xff);

	_isRunning = true;

	// Initialize SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return !success;	
	}

	// Load the apple-eating sound effect
	eatApple = Mix_LoadWAV("sounds/apple_bite.wav");
	if (eatApple == nullptr)
	{
		return !success;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		errorTTF("SDL_ttf couldn't be initialized!");
		return !success;
	}

	// Open the font
	_font = TTF_OpenFont("fonts/courier_new.ttf", 30);
	if (_font == nullptr)
	{
		errorTTF("Failed to load font!");
		return !success;
	}

	// Set the font texture when player loses
	gameState.ttfTexture = TextureLoader::loadTextureTTF(_font, "Game Over (Press Space to Restart)", _renderer);

	// Set coordinates for game objects and load their images as textures
	_snake = std::make_shared<Snake>(Snake(SNAKE_X_OFFSET, SNAKE_Y_OFFSET));
	gameState.snakeTexture = TextureLoader::loadTexture("resources/lil_snake.bmp", _renderer);

	_food = std::make_shared<Food>(Food(FOOD_X_OFFSET, FOOD_Y_OFFSET));
	gameState.foodTexture = TextureLoader::loadTexture("resources/some_food.bmp", _renderer);

	return success;
}

// Process the controls the user inputs
void Game::processInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) 
	{
		_isRunning = false;
	}

	// Actions for player
	if (event.type == SDL_KEYDOWN) 
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_UP: if (_snake -> getCurrDir() != DOWN) _snake -> setDir(UP); break;
			case SDLK_DOWN: if (_snake -> getCurrDir() != UP) _snake -> setDir(DOWN); break;
			case SDLK_LEFT: if (_snake -> getCurrDir() != RIGHT) _snake -> setDir(LEFT); break;
			case SDLK_RIGHT: if (_snake -> getCurrDir() != LEFT) _snake -> setDir(RIGHT); break;
			case SDLK_SPACE:
				_snake -> restart(); 
				_food -> restart();
				gameState.gameOver = false;
				break;
		}
	}
}

// Update the game state
void Game::update()
{
	if (gameState.gameOver) return;

	_snake -> move();
	gameState.gameOver = _snake -> checkSelfCollision();

	SDL_Rect s = _snake -> getHead(), f = _food -> getFood();

	if (s.y == f.y && s.x == f.x)
	{
		if (Mix_PlayChannel(-1, eatApple, 0) == -1) return;
		_snake -> grow();
		_food -> newLocation();
	}
}

// Reference: https://wiki.libsdl.org/SDL_RenderPresent
// Render the updated game components onto the screen
void Game::render()
{
	// Clear current rendering target with drawing color
	SDL_RenderClear(_renderer);

	// Render the snake head to tail {head ... tail}
	auto tmp = _snake -> getAll();
	for (auto i = tmp.begin(); i != tmp.end(); ++i)
	{
		SDL_RenderCopy(_renderer, gameState.snakeTexture, nullptr, &((*i).part));
	}

	// Copy portion of texture to render target
	SDL_RenderCopy(_renderer, gameState.foodTexture, nullptr, &(_food -> getFood()));

	if (gameState.gameOver)
	{
		int tw = 0, th = 0;

		// Get attributes of ttf texture (width and height)
		SDL_QueryTexture(gameState.ttfTexture, nullptr, nullptr, &tw, &th);
		SDL_Rect ds = {TEXT_W_OFFSET, SCREEN_HEIGHT/2 - TEXT_H_OFFSET, tw, th};
		SDL_RenderCopy(_renderer, gameState.ttfTexture, nullptr, &ds);
	}

	// Update screen with any rendering performed since previous call
	SDL_RenderPresent(_renderer);
}

void Game::close()
{
	SDL_DestroyWindow(_window);
	_window = nullptr;
	SDL_DestroyRenderer(_renderer);
	_renderer = nullptr;
	TTF_CloseFont(_font);
	_font = nullptr;
	Mix_FreeChunk(eatApple);
	eatApple = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
	TTF_Quit();
}

void Game::error(const std::string& errorMsg)
{
	std::cout << errorMsg << " SDL Error: " << SDL_GetError() << "\n";	
}

void Game::errorTTF(const std:: string& errorMsg)
{
	std::cout << errorMsg << " SDL Error: " << TTF_GetError() << "\n";	
}
