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

	controladorJson->leerArchivo(argumentoConsola);

	Juego *juego = new Juego();
	delete juego;

	return 0;

}

