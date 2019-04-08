#ifndef HEADERS_CONTROLER_CONTROLADORJSON_HPP_
#define HEADERS_CONTROLER_CONTROLADORJSON_HPP_

#include "controler/json.hpp"
#include <string>
#include <tuple>
#include <vector>
#include <iostream>

using json = nlohmann::json;
class ControladorJson{

	public:

		void leerArchivo();
		int alturaVentana();
		int anchoVentana();
		int cantidadFPS();
		int alturaPersonaje(std::string);
		int anchoPersonaje(std::string);
		int cantidadFondos();
		bool esfullscreen();

		std::string nivelDebug();
		std::string pathFondo(int zindex);
		std::string pathImagen(std::string nombrePersonaje);
		void leerArchivoDefault();
		std::string MenuImage();

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
		std::string menuImage;

		//Valores por defecto
		const std::string configPathDefault = "source/default/config.json";
		const std::string nivel_debug_default = "DEBUG";
		const int altura_ventana_default = 600;
		const int ancho_ventana_default = 800;
		const bool fullscreen_default = false;
		const int cantidad_personajes_default = 4;
		const int cantidad_fondos_default = 3;
		const int FPS_default = 60;
		void setMenuImage(json j);

		const std::string nombre_personaje_default = "CapitanAmerica";
		std::string filepath_personaje_default = "contents/auxiliar/personaje_auxiliar_sprite.png";
		int height_personaje_default = 320;
		int width_personaje_default = 200;
		int zindex_personaje_default = 99;

		//Rangos aceptados
		const int rango_altura_ventana[2] = {400, 2000};
		const int rango_ancho_ventana[2] = {600, 4000};
		const int rango_FPS[2] = {30, 60};

		void setLogLevel(json j)throw();
		void setAlturaVentana(json j)throw();
		void setAnchoVentana(json j)throw();
		void setPantallaCompleta(json j)throw();
		void setFPS(json j)throw();
		void setCantidadPersonajes(json j)throw();
		void setCantidadFondos(json j)throw();
		void setFondos(json j)throw();
		void setPersonajes(json j)throw();
		/*
		void setAlturaPersonaje(json j)throw();
		void setAnchhoPersonaje(json j)throw();

		*/


};

#endif
