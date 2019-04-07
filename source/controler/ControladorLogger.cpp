#include <controler/ControladorLogger.hpp>
#include <fstream>

ControladorLogger::ControladorLogger(){

	std::ofstream file;
	try{
		file.open(nombreArchivo,std::ofstream::trunc);
		file << "Archivo de logging creado!" <<" ; " << obtenerTiempo();
	}
	catch(int e){
		file.open(nombreArchivoRepuesto, std::fstream::trunc);
		file << "Archivo de logging de repuesto creado!" <<" ; " << obtenerTiempo();
	}
	file.close();

}

int ControladorLogger::registrarEvento(std::string nivel_debug_evento,  std::string mensaje ){

	int registrado = 0;
	int noRegistrable = 1;
	int registrablePeroNoRegistrado = 2;

	if(nivel_debug_evento.compare("INFO") == 0 && nivelDebug.compare("ERROR")== 0  ) return noRegistrable;
	if(nivel_debug_evento.compare("DEBUG") == 0 && nivelDebug.compare("DEBUG")!= 0  ) return noRegistrable;


	std::ofstream file;

	try{
		file.open(nombreArchivo, std::fstream::app);
		file << nivel_debug_evento <<" ; " << mensaje << " ; " << obtenerTiempo() ;
		file.close();
		return registrado;
	}

	catch (int e){
		//No se puede abrir ni crear el archivo log.txt. Es bastante grave. Se trata de crear otro
		try{
			file.open(nombreArchivoRepuesto, std::fstream::app);
			file << nivel_debug_evento <<" ; " << mensaje << " ; " << obtenerTiempo() ;
			file.close();
			return registrado;
		}

		catch(int e2){
			return registrablePeroNoRegistrado;
		}

	}
}

void ControladorLogger::setNivelDebug(std::string nivel_debug){
	nivelDebug = nivel_debug;
}

std::string ControladorLogger::obtenerTiempo(){
	time_t fecha = time(NULL);
	return ctime(&fecha);
}


