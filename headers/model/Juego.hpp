#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorTeclado.hpp>
#include <Parallax.hpp>
#include <TexturasFondos.hpp>
#include <JuegoCliente.hpp>
#include <Equipo.hpp>
#include<vector>

#define CANTIDAD_MAXIMA_JUGADORES 4
extern ControladorJson *controladorJson;

class Jugador;
class JuegoCliente;
class Equipo;
using namespace std;

class Juego{

	public:

		Juego();
		~Juego();
		bool running() {return isRunning;}
		void gameLoop();
		std::vector<std::tuple<std::string,SDL_Rect , SDL_Rect,SDL_RendererFlip>> dibujar();
		void teclear(SDL_Event evento);
		void verificarCambioDeLado();
		void crearEquipos();
		void crearJugador(string nombre,int cliente);
		static bool compare_zindexs(std::tuple<Jugador *, int> zindex1, std::tuple<Jugador *, int> zindex2);
		std::vector<std::tuple<Jugador *, int>> obtenerOrdenDibujo();
		void crearJugadores(string nombre, const string &filePath, int cliente);

	private:

		ControladorTeclado *teclado;
		Jugador *jugadorActualEquipo1;
		Jugador *jugadorActualEquipo2;
		Parallax *parallax;
		Uint32 startTime;
		vector<Jugador*> jugadores={NULL,NULL,NULL,NULL};
		Equipo *equipo1;
		Equipo *equipo2 ;
		bool isRunning;
		int FPS = controladorJson->cantidadFPS();
		unsigned MAX_FRAME_TIME = 1000 / FPS;

};

#endif
