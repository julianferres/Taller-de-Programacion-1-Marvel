#ifndef HEADERS_CONTROLER_CONTROLADORJSON_HPP_
#define HEADERS_CONTROLER_CONTROLADORJSON_HPP_

#include "controler/json.hpp"
#include <string>
#include <tuple>
#include <vector>

using json = nlohmann::json;
typedef std::tuple<std::string, std::string, int, int, int, std::string> tuplaPersonaje;

class ControladorJson{

	public:

		int alturaVentana();
		int anchoVentana();
		int cantidadFPS();
		int alturaPersonaje(std::string);
		int anchoPersonaje(std::string);
		int zindexPersonaje(std::string nombrePersonaje);
		int cantidadFondos();
		int cantidadJugadores();
		int cantidadPersonajes();
		int getPosicionXInicialJugador1();
		int getPosicionXInicialJugador2();
		int getLimiteFondoIzq();
		int getLimiteFondoDer();
		int getAlturaPiso();
		bool esfullscreen();
		bool existePersonaje(std::string);
		std::string nivelDebug();
		std::string pathFondo(int zindex);
		std::string pathImagen(std::string nombrePersonaje);
		std::string pathBoton(std::string nombrePersonaje);
		std::string nombrePersonajeI(int i);
		std::string menuImage();
		std::string jugador1Personaje(int numero);
		std::string jugador2Personaje(int numero);
		void leerArchivo(std::string argumentoConsola);
		void leerArchivoDefault();
		void cambiarPantallaCompleta();
		void maximizarVentana(int ancho, int alto);
		void setPersonajeJugador(int personaje, int jugador, std::string nombre);

	private:

		int altura_ventana;
		int ancho_ventana;
		int cantidad_personajes;
		int cantidad_fondos;
		int FPS;
		int cantidad_jugadores;
		int height_personaje_default = 200;
		int width_personaje_default = 200;
		int zindex_personaje_default = 99;
		bool fullscreen;
		std::string nivel_debug;
		std::vector<tuplaPersonaje> personajes;
		std::vector<std::tuple<std::string, int>> fondos;
		std::string configPath = "source/config/config.json";
		std::vector<std::string> personajesJugador1;
		std::vector<std::string> personajesJugador2;
		const std::string configPathDefault = "source/default/configaux.json";
		const std::string nivel_debug_default = "DEBUG";
		const int altura_ventana_default = 600;
		const int ancho_ventana_default = 800;
		const int altura_personaje_default = 300;
		const int ancho_personaje_default = 200;
		const int cantidad_personajes_default = 4;
		const int cantidad_fondos_default = 3;
		const int FPS_default = 60;
		const bool fullscreen_default = false;
		const std::string nombre_personaje_default = "sinSprite";

		const int rango_altura_ventana[2] = {600, 1000};
		const int rango_ancho_ventana[2] = {800, 1400};
		const int rango_altura_personaje[2] = {50,400};
		const int rango_ancho_personaje[2] = {50,350};
		const int rango_FPS[2] = {30, 60};

		void setLogLevel(json j, std::string argumentoConsola)throw();
		void setAlturaVentana(json j)throw();
		void setAnchoVentana(json j)throw();
		void setPantallaCompleta(json j)throw();
		void setFPS(json j)throw();
		void setCantidadJugadores(json j)throw();
		void setCantidadPersonajes(json j)throw();
		void setCantidadFondos(json j)throw();
		void setFondos(json j)throw();
		void setPersonajes(json j)throw();
		void elegirPersonajes(json j) throw();
		void fallaPersonajes();

		int posicionXInicialJugador1; //= controladorJson->anchoVentana() * 1/16;
		int posicionXInicialJugador2; //= controladorJson->anchoVentana() *3/4;
		int limiteFondoIzq;// = controladorJson->anchoVentana() * 1/8;
		int limiteFondoDer;// = controladorJson->anchoVentana() * 15/16;
		int altura_piso = 80;

};

#endif
