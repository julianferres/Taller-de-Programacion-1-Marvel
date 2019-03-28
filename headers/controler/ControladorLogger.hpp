#ifndef HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_
#define HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_

#include "Evento.hpp"
#include <ctime>


class ControladorLogger{

public:

	ControladorLogger( std::string nivelDebug);
	int registrarEvento( Evento *event); //Registra el evento en el archivo -nombreArchivo- y devuelve si pudo hacerlo.

private:

	int nivelDebug;
	std::string nombreArchivo = "source/config/log.txt";
	std::string nombreArchivoRepuesto = "source/config/log_repuesto.txt";
};


#endif /* HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_ */
