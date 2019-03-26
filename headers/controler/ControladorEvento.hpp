/*
 * ControladorEvento.hpp
 *
 *  Created on: 26 mar. 2019
 *      Author: lucas
 */

#ifndef HEADERS_CONTROLER_CONTROLADOREVENTO_HPP_
#define HEADERS_CONTROLER_CONTROLADOREVENTO_HPP_
#include <string>
#include <ctime>
#include <iostream>

class Evento{
public:
	std::string mensaje();
	std::string nivelDebug();
	std::tm fecha();

private:
	std::string mensaje;
	std::string nivel_debug;
	std::tm fecha;
};




#endif /* HEADERS_CONTROLER_CONTROLADOREVENTO_HPP_ */
