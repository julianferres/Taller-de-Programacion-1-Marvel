#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <Parallax.hpp>

extern ControladorJson *controladorJson;

class Jugador;

class Juego{

	public:

		Juego();
		~Juego();
		bool running() {return isRunning;}
		void gameLoop();
		void dibujar(ControladorGrafico &grafico);
		void iniciarFondo(ControladorGrafico &graficos);
		void teclear(ControladorGrafico &grafico, SDL_Event evento);
		void verificarCambioDeLado();
		static bool compare_zindexs(std::tuple<Jugador *, int> zindex1, std::tuple<Jugador *, int> zindex2);
		std::vector<std::tuple<Jugador *, int>> obtenerOrdenDibujo();

	private:
		ControladorGrafico *graficos;
		bool isRunning;
		Jugador *jugador1;
		Jugador *jugador2;
		Parallax *parallax;
		Uint32 startTime;
		int FPS = controladorJson->cantidadFPS();
		unsigned MAX_FRAME_TIME = 1000 / FPS;

};

#endif
