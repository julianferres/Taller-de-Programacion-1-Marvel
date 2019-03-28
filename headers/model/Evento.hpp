#ifndef HEADERS_MODEL_EVENTO_HPP_
#define HEADERS_MODEL_EVENTO_HPP_

#include <string>
#include <ctime>

class Evento{

public:

	Evento( std::string fecha, std::string nivel_debug, std::string mensaje );

	int getNivelDebug();
	std::string getNivel_Debug();
	std::string getMensaje();
	std::string getFecha();

private:

	int nivelDebug;
	std::string nivel_Debug;
	std::string mensaje;
	std::string fecha;

};

#endif /* HEADERS_MODEL_EVENTO_HPP_ */
