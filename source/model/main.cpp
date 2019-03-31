#include <Juego.hpp>
#include <controler/ControladorJson.hpp>
#include <controler/ControladorLogger.hpp>
#include <Parallax.hpp>


time_t my_time = time(NULL);
ControladorJson *controladorJson = new ControladorJson();
ControladorLogger *controladorLogger = new ControladorLogger();

Parallax *p = nullptr;

int main(int argc, char **argv){

	controladorJson->leerArchivo();
	controladorLogger->registrarEvento("INFO", "Juego iniciado", ctime(&my_time));
	controladorLogger->registrarEvento("INFO","Cantidad de FPS: "+std::to_string(controladorJson->cantidadFPS()) , ctime(&my_time));
	Juego juego;

	return 0;

}

