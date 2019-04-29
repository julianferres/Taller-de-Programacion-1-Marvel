#include <Juego.hpp>
#include <string>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>
#include <Servidor.hpp>
#include <Server.hpp>
#include <Cliente.hpp>

ControladorJson *controladorJson = new ControladorJson();
ControladorLogger *controladorLogger = new ControladorLogger();

int main(int argc, char **argv){
	std::string argumentoConsola ;
	controladorLogger->registrarEvento("INFO", "main::Comienzo a leer el json");
	controladorJson->leerArchivo(argumentoConsola);

	bool iniciarJuego = true;
	if(argc == 2){
		argumentoConsola = argv[1];
		if(argumentoConsola == "Server"){
			Server *server = new Server();
		}
	}
	else if(argc == 3){
		argumentoConsola = argv[1];
		if(argumentoConsola=="Cliente"){
			Cliente * cliente1 = new Cliente(argv[2]);

		}
	}


	else
		argumentoConsola = "";

	controladorLogger->registrarEvento("INFO", "main::Json leido. Comienzo el juego");
	Juego *juego = new Juego();
	delete juego;
	controladorLogger->registrarEvento("INFO", "main::Juego Finalizado");
	return 0;

}

