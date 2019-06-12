#ifndef HEADERS_MODEL_ROUND_HPP_
#define HEADERS_MODEL_ROUND_HPP_

#include <Parallax.hpp>
#include <ControladorJson.hpp>
#include <Temporizador.hpp>

class Equipo;

extern ControladorJson *controladorJson;

class Round{
public:
	Round(int num);
	~Round();
	Parallax * getParallax();
	int getNumero();
	void iniciarTiempo();
	bool finalizado();
	void actualizarTiempo();
	std::tuple<std::string,SDL_Rect, SDL_Rect ,SDL_RendererFlip > getTiempoDibujable();
	std::tuple<std::string,SDL_Rect, SDL_Rect ,SDL_RendererFlip > dibujarBanner();
private:

	int numero;
	Parallax *parallax;
	Temporizador *tiempo;
};



#endif /* HEADERS_MODEL_ROUND_HPP_ */
