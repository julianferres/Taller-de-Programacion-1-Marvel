#include <ControladorTexturas.h>

SDL_Texture* ControladorTexturas::LoadTexture(const char* texture ){
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Juego::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}
//TEST
//TEST EMA
//TEST MATI
//test ema2
//test branch log
