#ifndef HEADERS_MODEL_EVENTO_HPP_
#define HEADERS_MODEL_EVENTO_HPP_
#include <string>
#include <ctime>
#include <time.h>

class Evento{

public:

	Evento(std::string fecha, std::string nivel_debug,  std::string mensaje );
	std::string getFecha();
	int getNivelDebug();
	std::string getMensaje();

private:
	std::string fecha;
	int nivelDebug;
	std::string mensaje;

};

#endif /* HEADERS_MODEL_EVENTO_HPP_ */
