#ifndef HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_
#define HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_

#include <ctime>
#include <string>

class ControladorLogger{

public:

	ControladorLogger( );
	void setNivelDebug(std::string nivelDebug);
	int registrarEvento( std::string nivel_debug_evento,  std::string mensaje ,std::string fecha); //Registra el evento en el archivo -nombreArchivo- y devuelve si pudo hacerlo.
	std::string obtenerHora();

private:

	std::string nivelDebug;
	std::string nombreArchivo = "source/config/log.txt";
	std::string nombreArchivoRepuesto = "source/config/log_repuesto.txt";
};


#endif /* HEADERS_CONTROLER_CONTROLADORLOGGER_HPP_ */
