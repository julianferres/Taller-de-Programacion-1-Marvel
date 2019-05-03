#include <Juego.hpp>
#include <string>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>
#include <Server.hpp>
#include <Cliente.hpp>

ControladorJson *controladorJson = new ControladorJson();
ControladorLogger *controladorLogger = new ControladorLogger();

int main(int argc, char **argv){
	std::string argumentoConsola = argv[1];
	controladorLogger->crearLog(argumentoConsola);
	controladorLogger->registrarEvento("INFO", "main::Comienzo a leer el json");
	controladorJson->leerArchivo(argumentoConsola);
	controladorLogger->registrarEvento("INFO", "main::Json leido. Comienzo el juego");

	if(argc == 2){
		if(argumentoConsola == "Server"){
			Server *server = new Server();
		}
	}
	else if(argc == 3){
		if(argumentoConsola=="Cliente"){
			Cliente * cliente1 = new Cliente(argv[2]);
		}
	}

	controladorLogger->registrarEvento("INFO", "main::Juego Finalizado");
	return 0;

}

