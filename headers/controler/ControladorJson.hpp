#ifndef HEADERS_CONTROLER_CONTROLADORJSON_HPP_
#define HEADERS_CONTROLER_CONTROLADORJSON_HPP_

#include "controler/json.hpp"
#include <string>
#include <tuple>
#include <vector>
using json = nlohmann::json;
class ControladorJson{

	public:

		void leerArchivo();
		int alturaVentana();
		int anchoVentana();
		int cantidadFPS();
		int alturaPersonaje(std::string);
		int anchoPersonaje(std::string);
		bool esfullscreen();
		std::string nivelDebug();
		std::string pathFondo(int zindex);
		std::string pathImagen(std::string nombrePersonaje);
		void leerArchivoDefault();

	private:

		int altura_ventana;
		int ancho_ventana;
		bool fullscreen;
		int cantidad_personajes;
		int cantidad_fondos;
		int FPS;
		std::string nivel_debug;
		std::vector<std::tuple<std::string, std::string, int, int, int>> personajes;
		std::vector<std::tuple<std::string, int>> fondos;
		std::string configPath = "source/config/config.json";

		//Valores por defecto
		const std::string configPathDefault = "source/default/config.json";
		const std::string nivel_debug_default = "DEBUG";
		const int altura_ventana_default = 600;
		const int ancho_ventana_default = 800;
		const bool fullscreen_default = false;
		const int cantidad_personajes_default = 4;
		const int cantidad_fondos_default = 3;
		const int FPS_default = 60;

		//Rangos aceptados
		const int rango_altura_ventana[2] = {400, 800};
		const int rango_ancho_ventana[2] = {600, 1000};
		const int rango_FPS[2] = {30, 60};

		void setLogLevel(json j);
		void setAlturaVentana(json j);
		void setAnchoVentana(json j);
		void setPantallaCompleta(json j);
		void setAlturaPersonaje(json j);
		void setAnchhoPersonaje(json j);
		void setFPS(json j);
		void setCantidadPersonajes(json j);
		void setCantidadFondos(json j);



};

#endif
