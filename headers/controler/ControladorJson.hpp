#ifndef HEADERS_CONTROLER_CONTROLADORJSON_HPP_
#define HEADERS_CONTROLER_CONTROLADORJSON_HPP_

#include "controler/json.hpp"
#include <string>
#include <tuple>
#include <vector>

using json = nlohmann::json;
using namespace std;
typedef tuple<string, std::string, int, int, int, std::string> tuplaPersonaje;

class ControladorJson{

	public:

		int alturaVentana();
		int anchoVentana();
		int cantidadFPS();
		int alturaPersonaje(std::string);
		int anchoPersonaje(std::string);
		int zindexPersonaje(std::string nombrePersonaje);
		int cantidadFondos(int round);
		int cantidadPersonajes();
		int cantidadClientes();
		int getPosicionXInicialEquipo1();
		int getPosicionXInicialEquipo2();
		int getLimiteFondoIzq();
		int getLimiteFondoDer();
		int getAlturaPiso();
		int alturaPersonajeDefault();
		int anchoPersonajeDefault();
		bool esfullscreen();
		bool existePersonaje(string);
		void leerArchivo(string argumentoConsola);
		void leerArchivoDefault();
		void cambiarPantallaCompleta();
		void maximizarVentana(int ancho, int alto);
		void setPersonajeJugador(int personaje, int jugador, string nombre);
		string nivelDebug();
		string pathFondo(int zindex, int round);
		string pathImagen(string nombrePersonaje);
		string pathBoton(string nombrePersonaje);
		string nombrePersonajeI(int i);
		string menuImage();
		string jugador1Personaje(int numero);
		string jugador2Personaje(int numero);
		vector <string> getNombresPersonajes();
		vector<int>getZindexes(int round);
		int  TIEMPO_ROUND = 15;

	private:

		int altura_ventana;
		int ancho_ventana;
		int cantidad_personajes;
		int cantidad_rounds;
		vector<int> cantidad_fondos;
		int cantidad_clientes;
		int FPS;
		int cantidad_jugadores;
		int height_personaje_default = 200;
		int width_personaje_default = 200;
		int zindex_personaje_default = 99;
		bool fullscreen;

		string nivel_debug;
		vector<string> nombresPersonajes;
		vector<int>zindexes;
		vector<tuplaPersonaje> personajes;
		//vector<tuple<string, int>> fondos;
		vector<vector<tuple<string, int>>> escenarios;
		string configPath = "source/config/config.json";
		vector<string> personajesJugador1;
		vector<string> personajesJugador2;

		const string configPathDefault = "source/default/configaux.json";
		const string nivel_debug_default = "DEBUG";
		const int altura_ventana_default = 600;
		const int ancho_ventana_default = 800;
		const int altura_personaje_default = 300;
		const int ancho_personaje_default = 200;
		const int cantidad_personajes_default = 4;
		const int cantidad_fondos_default = 3;
		const int FPS_default = 60;
		const bool fullscreen_default = false;
		const string nombre_personaje_default = "SinSprite";
		const int rango_altura_ventana[2] = {600, 1000};
		const int rango_ancho_ventana[2] = {800, 1400};
		const int rango_altura_personaje[2] = {50,4000};
		const int rango_ancho_personaje[2] = {50,4000};
		const int rango_FPS[2] = {30, 120};

		void setLogLevel(json j, string argumentoConsola)throw();
		void setAlturaVentana(json j)throw();
		void setAnchoVentana(json j)throw();
		void setPantallaCompleta(json j)throw();
		void setFPS(json j)throw();
		void setCantidadJugadores(json j)throw();
		void setCantidadPersonajes(json j)throw();
		void setCantidadFondos(json j)throw();
		void setCantidadRounds(json j)throw();
		void setRounds(json j)throw();
		vector<tuple<string, int>> setFondos(json j, int round)throw();
		void setPersonajes(json j)throw();
		void elegirPersonajes(json j) throw();
		void fallaPersonajes();
		void setCantidadClientes(json j);

		int posicionXInicialJugador1; //= controladorJson->anchoVentana() * 1/16;
		int posicionXInicialJugador2; //= controladorJson->anchoVentana() *3/4;
		int limiteFondoIzq;// = controladorJson->anchoVentana() * 1/8;
		int limiteFondoDer;// = controladorJson->anchoVentana() * 15/16;
		int altura_piso = 60;

};

#endif
