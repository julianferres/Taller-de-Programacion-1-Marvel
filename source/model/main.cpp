#include <Juego.hpp>
#include <controler/ControladorJson.hpp>


Juego *juego = nullptr;


int main(int argc, char **argv){

	ControladorJson *controladorJson = new ControladorJson();
	controladorJson->leerArchivo();

	const int FPS = controladorJson->cantidadFPS();
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


