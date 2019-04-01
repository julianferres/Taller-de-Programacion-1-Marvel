#ifndef JUEGO_HPP
#define JUEGO_HPP
//juego
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorTeclado.hpp>
#include <Sprite.hpp>
#include <Parallax.hpp>

class Jugador;
class Parallax;

class Juego{

public:
	Juego();
	~Juego();
	bool running() {return isRunning;}
private:
	void gameLoop();
	void dibujar(ControladorGrafico &grafico);
	void actualizar(float tiempo);
	void dibujarFondo(ControladorGrafico &graficos);
	void teclear(SDL_Event evento,ControladorTeclado teclado);
	bool isRunning;
	Jugador *jugador1;
	Parallax *parallax;

};

#endif
