#include <Juego.hpp>
#include <string>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>

ControladorJson *controladorJson = new ControladorJson();
ControladorLogger *controladorLogger = new ControladorLogger();

int main(int argc, char **argv){
	std::string argumentoConsola ;
	if(argc == 2)
		argumentoConsola = argv[1];
	else
		argumentoConsola = "";
	controladorLogger->registrarEvento("INFO", "main::Comienzo a leer el json");
	controladorJson->leerArchivo(argumentoConsola);
	controladorLogger->registrarEvento("INFO", "main::Json leido. Comienzo el juego");
	Juego *juego = new Juego();
	delete juego;
	controladorLogger->registrarEvento("INFO", "main::Juego Finalizado");
	return 0;

}

