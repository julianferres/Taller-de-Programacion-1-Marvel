#include <controler/ControladorLogger.hpp>
#include <fstream>
#include <iostream>

extern time_t my_time;

ControladorLogger::ControladorLogger(){

	std::ofstream file;
	try{
		file.open(nombreArchivo,std::ofstream::trunc);
	}
	catch(int e){
		file.open(nombreArchivoRepuesto, std::fstream::trunc);
	}
	file <<  "INFO "<<" ; " << "Archivo de logging creado!" <<" ; " << ctime(&my_time);
	file.close();

}

int ControladorLogger::registrarEvento(std::string nivel_debug_evento,  std::string mensaje ,std::string fecha){
	/*valores de retorno:
		0: El evento se registro correctamente
		1: El evento no debia ser registrado debido al nivel de debug
		2: El evento debia ser registrado y no pudo registrarse*/

	int registrado = 0;
	int noRegistrable = 1;
	int registrablePeroNoRegistrado = 2;

	if(nivel_debug_evento.compare("INFO") == 0 && nivelDebug.compare("INFO")!= 0  ) return noRegistrable;
	if(nivel_debug_evento.compare("ERROR") == 0 && nivelDebug.compare("DEBUG")== 0  ) return noRegistrable;

	std::ofstream file;
	try{
		file.open(nombreArchivo, std::fstream::app);
		file << nivel_debug_evento <<" ; " << mensaje << " ; " << fecha ;
		file.close();
		return registrado;
	}
	catch (int e){
		//No se puede abrir ni crear el archivo log.txt. Es bastante grave. Se trata de crear otro
		try{
			file.open(nombreArchivoRepuesto, std::fstream::app);
			file << nivel_debug_evento <<" ; " << mensaje << " ; " << fecha ;
			file.close();
			return registrado;
		}
		catch(int e2){
			//El directorio parece estar  dañado. No se puede loggear.
			return registrablePeroNoRegistrado;
		}
	}
}

void ControladorLogger::setNivelDebug(std::string nivel_debug){
	nivelDebug = nivel_debug;
}


