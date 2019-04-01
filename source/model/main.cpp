#include <Juego.hpp>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>

ControladorJson *controladorJson = new ControladorJson();
ControladorLogger *controladorLogger = new ControladorLogger();

int main(int argc, char **argv){

	controladorJson->leerArchivo();
	Juego juego;

	return 0;

}

