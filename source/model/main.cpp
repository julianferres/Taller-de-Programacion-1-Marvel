#include <Juego.hpp>
#include <iostream>
#include <ControladorGrafico.hpp>
//pequeño test

//Juego *juego = nullptr;


int main(int argc, char **argv){

	Juego juego;
	return 0;
	/*const int FPS = 60;
	const int frameDelay = 1000/ FPS;
	Uint32 frameStart;
	int frameTime;
	ControladorGrafico graficos;

	juego = new Juego();

	juego-> init("Marvel vs Capcom",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while(juego -> running()){

		frameStart = SDL_GetTicks();

		juego-> handleEvents();
		juego-> update(frameTime);
		juego-> dibujar(graficos);

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime){
			SDL_Delay(frameDelay - frameTime);
		}


	}
	juego-> clean();

	return 0;
	*/
}
//Test branch


