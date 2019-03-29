#include <Juego.hpp>
#include <controler/ControladorJson.hpp>
#include <controler/ControladorLogger.hpp>


time_t my_time = time(NULL);
ControladorJson *controladorJson = new ControladorJson();
ControladorLogger *controladorLogger = new ControladorLogger(controladorJson->nivelDebug());

/*
int main(int argc, char **argv){

	controladorJson->leerArchivo();

	const int FPS = controladorJson->cantidadFPS();
	if(FPS < 30)
		controladorLogger->registrarEvento("ERROR","Los FPS son menores a 30",ctime(&my_time));


	const int frameDelay = 1000/ FPS;
	Uint32 frameStart;
	int frameTime;

	Juego *juego = new Juego();
	juego-> init("Marvel vs Capcom",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, controladorJson->alturaVentana(), controladorJson->anchoVentana(), controladorJson->esfullscreen());

	while(juego -> running()){

		frameStart = SDL_GetTicks();

		juego-> handleEvents();
		juego-> update();
		juego-> render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);

	}

	juego-> clean();

	return 0;

}*/


