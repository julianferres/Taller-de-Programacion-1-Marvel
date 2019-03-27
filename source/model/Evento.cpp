#include <Evento.hpp>

Evento::Evento(std::string fecha, std::string nivel_debug,  std::string mensaje ){
	int error = 1;
	int info = 2;
	int debug = 3;

	this->fecha = fecha;
	if(nivel_debug.compare("ERROR") == 0) this->nivelDebug = error;
	else if(nivel_debug.compare("INFO") == 0) this->nivelDebug = info;
	else this->nivelDebug = debug;
	//this->nivelDebug = nivel_debug;
	this->mensaje = mensaje;
}

std::string Evento::getFecha(){
	return fecha;
}

int Evento::getNivelDebug(){
	return nivelDebug;
}

std::string Evento::getMensaje(){
	return mensaje;
}


