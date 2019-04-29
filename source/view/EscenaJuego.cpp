#include <EscenaJuego.hpp>
#include <string>
#include <vector>

EscenaJuego::EscenaJuego(std::vector<std::tuple<std::string, int, int, int, int, SDL_RendererFlip>> escena){
	this->escena = escena;
}



