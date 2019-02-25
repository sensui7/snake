/*
	Steven Tran
	CS410
	Final Project
*/

#ifndef TEXTURE_LOADER
#define TEXTURE_LOADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextureLoader
{
	public:
		static SDL_Texture* loadTexture(const std::string& fileName, SDL_Renderer* renderer)
		{
			SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());							

			/* Optional way to set transparent background for the surface
			uint32_t colorKey = SDL_MapRGB(tmpSurface -> format, 0, 0, 0);
			SDL_SetColorKey(tmpSurface, SDL_TRUE, colorKey);
			*/

			SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			return tmpTexture;
		}

		static SDL_Texture* loadTextureTTF(TTF_Font* text, const std::string& textStr, SDL_Renderer* renderer)
		{
			SDL_Color color = { 0xff, 0x00, 0x00 };
			SDL_Surface* tmpSurface = TTF_RenderText_Solid(text, textStr.c_str(), color);
			SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			return tmpTexture;
		}

	private:
};

#endif

