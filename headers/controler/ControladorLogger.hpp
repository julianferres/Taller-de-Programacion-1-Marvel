#ifndef HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_
#define HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_

#include <ctime>
#include <Evento.hpp>

class ControladorLogger{

public:

	ControladorLogger(std::string nivelDebug);
	int registrarEvento(Evento *event); //Registra el evento en el archivo -nombreArchivo- y devuelve si pudo hacerlo.

private:
	int nivelDebug;
	std::string nombreArchivo;
};


#endif /* HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_ */
