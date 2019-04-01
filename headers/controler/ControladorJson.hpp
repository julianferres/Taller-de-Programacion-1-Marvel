#ifndef HEADERS_CONTROLER_CONTROLADORJSON_HPP_
#define HEADERS_CONTROLER_CONTROLADORJSON_HPP_

#include "controler/json.hpp"
#include <string>
#include <tuple>
#include <vector>

class ControladorJson{

	public:

		void leerArchivo();
		int alturaVentana();
		int anchoVentana();
		int cantidadFPS();
		bool esfullscreen();
		std::string nivelDebug();
		std::string pathImagen(int zindex);


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

};

#endif
