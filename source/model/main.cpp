#include <Juego.hpp>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>
#include <Parallax.hpp>


ControladorJson *controladorJson = new ControladorJson();
ControladorLogger *controladorLogger = new ControladorLogger();

Parallax *p = nullptr;

int main(int argc, char **argv){

	controladorJson->leerArchivo();
	controladorLogger->registrarEvento("INFO","Cantidad de FPS: "+std::to_string(controladorJson->cantidadFPS()) ,controladorLogger->obtenerHora() );
	Juego juego;

	return 0;

}

