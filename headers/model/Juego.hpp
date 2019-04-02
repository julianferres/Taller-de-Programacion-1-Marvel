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
		int MAX_FRAME_TIME = 1000 / FPS;
		Uint32 startTime;

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
