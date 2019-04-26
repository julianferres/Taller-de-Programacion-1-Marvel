#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorTeclado.hpp>
#include <Parallax.hpp>

extern ControladorJson *controladorJson;

class Jugador;

class Juego{

	public:

		Juego();
		~Juego();
		bool running() {return isRunning;}
		void gameLoop();
		void dibujar();
		void iniciarFondo();
		void teclear();
		void verificarCambioDeLado();
		static bool compare_zindexs(std::tuple<Jugador *, int> zindex1, std::tuple<Jugador *, int> zindex2);
		std::vector<std::tuple<Jugador *, int>> obtenerOrdenDibujo();

	private:

		ControladorGrafico *graficos;
		ControladorTeclado *teclado;
		Jugador *jugador1;
		Jugador *jugador2;
		Parallax *parallax;
		Uint32 startTime;
		void startGameMenu();
		bool isRunning;
		int FPS = controladorJson->cantidadFPS();
		unsigned MAX_FRAME_TIME = 1000 / FPS;

};

#endif
