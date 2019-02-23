#ifndef SNAKE
#define SNAKE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <list>

class Snake
{
	public:
		Snake(int32_t pX, int32_t pY, int32_t vX, int32_t vY) : _posX(pX), _posY(pY), _velX(vX), _velY(vY), _texture(nullptr) {}
		Snake() { SDL_DestroyTexture(_texture); }
		~Snake() {}

		SDL_Texture* getTexture()
		{
			return _texture;
		}

		void setTexture(SDL_Renderer*& renderer, const std::string& resource)
		{
			SDL_Surface* tmpSurface = IMG_Load(resource.c_str());
			_texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
		}
			
	private:
		int32_t _posX, _posY;
		int32_t _velX, _velY;	

		SDL_Texture* _texture;
};

#endif

