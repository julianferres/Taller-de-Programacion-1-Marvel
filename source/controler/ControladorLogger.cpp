#include <controler/ControladorLogger.hpp>
#include <fstream>
#include <iostream>

extern time_t my_time;

ControladorLogger::ControladorLogger(){

	nivelDebug = "DEBUG";
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

void ControladorLogger::setNivelDebug(std::string nivel_debug){
	nivelDebug = nivel_debug;
}

int ControladorLogger::registrarEvento(std::string nivel_debug_evento,  std::string mensaje ,std::string fecha){
	/*valores de retorno:
		0: El evento se registro correctamente
		1: El evento no debia ser registrado debido al nivel de debug
		2: El evento debia ser registrado y no pudo registrarse*/

	int registrado = 0;
	int noRegistrable = 1;
	int registrablePeroNoRegistrado = 2;

	if(nivelDebug.compare("ERROR") == 0 && nivel_debug_evento.compare("ERROR")!= 0  ) return noRegistrable;
	if(nivelDebug.compare("INFO") == 0 && nivel_debug_evento.compare("DEBUG")== 0  ) return noRegistrable;


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

