#ifndef HEADERS_CONTROLER_CONTROLADORJSON_HPP_
#define HEADERS_CONTROLER_CONTROLADORJSON_HPP_
#include <string>
#include <iostream>
#include <list>

class ControladorJson{
public:
	void leerArchivo();


private:
	int cantidad_atributos_personaje = 5;
	int altura_ventana;
	int ancho_ventana;
	std::string nivel_debug;
	int cantidad_personajes;
	std::list<std::list< std::string>> personajes;
};



#endif /* HEADERS_CONTROLER_CONTROLADORJSON_HPP_ */
