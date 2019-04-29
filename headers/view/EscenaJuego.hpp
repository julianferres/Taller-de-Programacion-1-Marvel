#ifndef ESCENAJUEGO_HPP_
#define ESCENAJUEGO_HPP_
#include <vector>
#include <tuple>
#include <SDL2/SDL_image.h>
#include <string>

class EscenaJuego{

	public:
		EscenaJuego(std::vector<std::tuple<std::string, int, int, int, int, SDL_RendererFlip>> escena);

	private:
		//nombre, x, y, alto, ancho, flip
		std::vector<std::tuple<std::string, int, int, int, int, SDL_RendererFlip>> escena;

};


#endif
