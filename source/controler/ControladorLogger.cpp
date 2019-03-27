#include <controler/ControladorLogger.hpp>
#include <fstream>
#include <iostream>

ControladorLogger::ControladorLogger(std::string nivelDebug){
		nivel_debug = nivelDebug;
}

bool ControladorLogger::registrarEvento(Evento *event){
		if ( nivel_debug.compare(event->getNivelDebug() ) != 0)
		return false;

	std::ofstream file;
	try{
		file.open("source/config/log.txt"); //Verificar la ruta
		file << event->getNivelDebug() <<"; " << event->getMensaje() <<"; " << event->getFecha();
		file.close();
		return true;
	}
	catch (int e){
		//No se puede abrir el archivo log.txt
		//Es bastante grave
		//Crear otro archivo
		return false;
	}
}


