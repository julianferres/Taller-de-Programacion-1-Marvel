/*
 * ControladorLogger.hpp
 *
 *  Created on: 26 mar. 2019
 *      Author: lucas
 */

#ifndef HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_
#define HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_

#include <iostream>
#include <string>
#include <ctime>

class ControladorLogger{
public:
	bool registrarEvento();
	//Registra el evento en el archivo -nombreArchivo- y devuelve si pudo hacerlo.
private:
	std::string nivel_debug;
	std::string nombreArchivo;
};



#endif /* HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_ */
