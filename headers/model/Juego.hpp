#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorTeclado.hpp>
#include <ControladorColisiones.hpp>
#include <Parallax.hpp>
#include <JuegoCliente.hpp>
#include <Equipo.hpp>
#include<vector>
#include <Round.hpp>

#define CANTIDAD_MAXIMA_JUGADORES 4
extern ControladorJson *controladorJson;

class Jugador;
class JuegoCliente;
class Equipo;
class ControladorColisiones;
using namespace std;

class Juego{

	public:

		Juego();
		~Juego();
		std::vector<std::string> gameMenu();
		std::vector<std::tuple<std::string,SDL_Rect , SDL_Rect,SDL_RendererFlip>> dibujar();
		std::vector<std::tuple<std::string,SDL_Rect , SDL_Rect,SDL_RendererFlip>> dibujarPantallaFinal();
		void teclear(SDL_Event evento,int tipoTeclado);
		void verificarCambioDeLado();
		void crearEquipos();
		void crearJugador(string nombre,int cliente);
		static bool compare_zindexs(std::tuple<Jugador *, int> zindex1, std::tuple<Jugador *, int> zindex2);
		std::vector<std::tuple<Jugador *, int>> obtenerOrdenDibujo();
		void crearJugadores(string nombre, const string &filePath, int cliente);
		void actualizarConexion(int idCliente);
		Equipo * getEquipo1();
		Equipo * getEquipo2();
		ControladorColisiones* controladorColisiones;
		int numeroRound();
		void nuevoRound();
		void decidirGanadorRoundAnterior();
		void iniciarRound();
		bool roundFinalizado();
		bool running();
		void actualizarTiempo();
		std::vector<std::tuple<std::string,SDL_Rect , SDL_Rect,SDL_RendererFlip>> dibujarBannerRound();
		std::tuple<std::string,SDL_Rect , SDL_Rect,SDL_RendererFlip> obtenerResultadosParciales1Dibujables();
		std::tuple<std::string,SDL_Rect , SDL_Rect,SDL_RendererFlip> obtenerResultadosParciales2Dibujables();
		void reiniciarPersonajes();
		void obtenerVidas(int *vidas);
		void reiniciarVidas();
		void cambiarEstadoTiempo();
		vector<string>getSonidos(vector<string>sonidos);
		void finalizarRound(int equipoGanador);
		bool hayGanador();
		int getTotalEquipo1();
		int getTotalEquipo2();
		void verificarMuerte(Equipo * equipo);
		vector<string> sonidoGanadorOPerdedor(int cliente);

	private:
		std::vector<int>resultados = {0,0,0};
		//vector<Equipo*> ganadores;
		bool tiempoCorriendo = true;
		ControladorTeclado *teclado;
		Jugador *jugadorActualEquipo1;
		Jugador *jugadorActualEquipo2;
		Parallax *parallax;
		Round *roundActual;
		Uint32 startTime;
		vector<Jugador*> jugadores={NULL,NULL,NULL,NULL};
		Equipo *equipo1;
		Equipo *equipo2 ;
		bool isRunning;
		string jugadorMuerto="";
		int FPS = controladorJson->cantidadFPS();
		unsigned MAX_FRAME_TIME = 1000 / FPS;
		int ancho_ventana;
		int alto_ventana;
		int ancho_maximo_ventana = 1400;
		int alto_maximo_ventana = 1000;
		map<int,bool>sonidoEnviado;

};

#endif
