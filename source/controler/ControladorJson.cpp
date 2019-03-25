#include <controler/ControladorJson.hpp>
#include "controler/json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <iterator>

void ControladorJson::leerArchivo(){
	using json = nlohmann::json;

	std::ifstream ifs ("source/config/config.json", std::ifstream::in);
	json j = json::parse(ifs);

	altura_ventana = j["window"]["height"];
	ancho_ventana = j["window"]["width"];
	nivel_debug = j["debug"];
	cantidad_personajes = j["characters"].size();

	std::list<std::string> personaje;
	for (int i = 0; i < cantidad_personajes; i++){
		personaje.push_back(j["characters"][i]["name"]);
		personaje.push_back(j["characters"][i]["filepath"]);
		//Faltan los demas atributos
		personajes.push_back(personaje);
		personaje.clear();
	}

	//Ejemplo para recorrer listas;
	/*std::list<std::list< std::string>>::iterator it_personajes = personajes.begin();
	std::list<std::string>::iterator it;
	for(int i = 0; i < 2; i++){
		it = (*it_personajes).begin();
		std::cout << ' ' << *(it) << std::endl;
		std::cout << ' ' << *(++it) << std::endl;
		it_personajes++;
	}*/
}
