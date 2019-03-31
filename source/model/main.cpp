#include <Juego.hpp>
#include <controler/ControladorJson.hpp>
#include <controler/ControladorLogger.hpp>
#include <Parallax.hpp>


time_t my_time = time(NULL);
ControladorJson *controladorJson = new ControladorJson();
ControladorLogger *controladorLogger = new ControladorLogger(controladorJson->nivelDebug());
Parallax *p = nullptr;

int main(int argc, char **argv){

	std::cout << "Creo al objeto!" << std::endl;
	controladorJson->leerArchivo();
	std::cout << controladorJson->cantidadFPS() << std::endl;
	Juego juego;

	return 0;

}

