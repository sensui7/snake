#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include <SDL2/SDL.h>
#include <string>

class TextureLoader
{
	public:
		static SDL_Texture* loadTexture(const std::string& fileName, SDL_Renderer* renderer)
		{
			SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());							

			uint32_t colorKey = SDL_MapRGB(tmpSurface -> format, 0, 0, 0);
			SDL_SetColorKey(tmpSurface, SDL_TRUE, colorKey);

			SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			return tmpTexture;
		}

	private:
};

#endif

