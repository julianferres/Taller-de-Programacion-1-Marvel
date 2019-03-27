#include <controler/ControladorLogger.hpp>
#include <fstream>
#include <iostream>

ControladorLogger::ControladorLogger(std::string nivel_debug){
	int error = 1;
	int info = 2;
	int debug = 3;

	if(nivel_debug.compare("ERROR") == 0) this->nivelDebug = error;
	else if(nivel_debug.compare("INFO") == 0) this->nivelDebug = info;
	else this->nivelDebug = debug;
	nombreArchivo = "source/config/log.txt";

}

int ControladorLogger::registrarEvento(Evento *event){
	/*valores de retorno:
		0: El evento se registro correctamente
		1: El evento no debia ser registrado debido al nivel de debug
		2: El evento debia ser registrado y no pudo registrarse
	*/
	int registrado = 0;
	int noRegistrable = 1;
	int registrablePeroNoRegistrado = 2;

	/*if ( nivelDebug.compare(event->getNivelDebug() ) != 0)
		return false;*/
	if ((event->getNivelDebug()) > nivelDebug) return noRegistrable;

	std::ofstream file;
	try{
		file.open(nombreArchivo, std::fstream::app); //Verificar la ruta
		file << event->getNivelDebug() <<"; " << event->getMensaje() <<"; " << event->getFecha();
		file.close();
		return registrado;
	}
	catch (int e){
		//No se puede abrir ni crear el archivo log.txt. Es bastante grave. Se trata de crear otro
		nombreArchivo = "source/config/log_repuesto.txt";
		try{
			file.open(nombreArchivo, std::fstream::app);
			file << event->getNivelDebug() <<"; " << event->getMensaje() <<"; " << event->getFecha();
			file.close();
			return registrado;
		}
		catch(int e2){
			//El directorio parece estar  dañado. No se puede loggear.
			return registrablePeroNoRegistrado;
		}
	}
}


