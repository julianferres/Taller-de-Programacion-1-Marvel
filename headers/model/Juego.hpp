#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorTeclado.hpp>
#include <ControladorJson.hpp>
#include <Sprite.hpp>
#include <Parallax.hpp>

extern ControladorJson *controladorJson;

class Jugador;
class Parallax;

class Juego{

	public:

		Juego();
		~Juego();
		bool running() {return isRunning;}
		int FPS = controladorJson->cantidadFPS();
		unsigned MAX_FRAME_TIME = 1000 / FPS;
		Uint32 startTime;

	private:

		void gameLoop(int posicionMoverFondoIzq, int posicionMoverFondoDer);
		void dibujar(ControladorGrafico &grafico);
		void dibujarFondo(ControladorGrafico &graficos);
		void teclear(SDL_Event evento,ControladorTeclado teclado, int posicionMoverFondoIzq, int posicionMoverFondoDer);
		bool isRunning;
		Jugador *jugador1;
		Jugador *jugador2;
		Parallax *parallax;

};

#endif
