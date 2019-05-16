#include <Juego.hpp>
#include <string>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>
#include <Cliente.hpp>
#include <Servidor.hpp>

ControladorJson *controladorJson = new ControladorJson();
ControladorLogger *controladorLogger = new ControladorLogger();

int main(int argc, char **argv){
	std::string argumentoConsola = argv[1];
	controladorLogger->crearLog(argumentoConsola);
	controladorLogger->registrarEvento("INFO", "main::Comienzo a leer el json");
	controladorJson->leerArchivo(argumentoConsola);
	controladorLogger->registrarEvento("INFO", "main::Json leido. Comienzo el juego");

	if(argc == 3 && argumentoConsola == "Server" ){
		Servidor *servidor = new Servidor(atoi(argv[2]));
	}
	else if(argc == 4 && argumentoConsola=="Cliente"){
		Cliente * cliente1 = new Cliente(argv[2],atoi(argv[3]));
	}

	controladorLogger->registrarEvento("INFO", "main::Juego Finalizado");
	return 0;

}

