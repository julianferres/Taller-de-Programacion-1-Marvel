#include <Evento.hpp>

Evento::Evento(std::string fecha, std::string nivel_debug,  std::string mensaje ){
		this->fecha = fecha;
		this->nivel_debug = nivel_debug;
		this->mensaje = mensaje;
}

std::string Evento::getFecha(){
	return fecha;
}

std::string Evento::getNivelDebug(){
	return nivel_debug;
}

std::string Evento::getMensaje(){
	return mensaje;
}


