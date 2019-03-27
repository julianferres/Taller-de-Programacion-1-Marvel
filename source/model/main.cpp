#include <Juego.hpp>
#include <Evento.hpp>
#include <controler/ControladorJson.hpp>
#include <controler/ControladorLogger.hpp>


Juego *juego = nullptr;
time_t my_time = time(NULL);


int main(int argc, char **argv){

	ControladorJson *controladorJson = new ControladorJson();
	controladorJson->leerArchivo();

	ControladorLogger *controladorLogger = new ControladorLogger(controladorJson->nivelDebug());


	const int FPS = controladorJson->cantidadFPS();
	if(FPS > 30){
		Evento *event = new Evento(ctime(&my_time),"ERROR","Los FPS son mayores a 30");
		controladorLogger->registrarEvento(event);
	}

	const int frameDelay = 1000/ FPS;
	Uint32 frameStart;
	int frameTime;

	juego = new Juego();
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

}


