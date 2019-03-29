#include <Parallax.hpp>
#include <iostream>

Parallax *p = nullptr;


int main(int argc, char **argv){
	const int FPS = 60;
	const int frameDelay = 1000/ FPS;
	Uint32 frameStart;
	int frameTime;

	p = new Parallax();
	std::cout << "Creo al objeto!" << std::endl;

	return 0;

}
/*
 int main(int argc, char **argv){

	const int FPS = 60;
	const int frameDelay = 1000/ FPS;
	Uint32 frameStart;
	int frameTime;

	juego = new Juego();

	juego-> init("Marvel vs Capcom",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while(juego -> running()){

		frameStart = SDL_GetTicks();

		juego-> handleEvents();
		juego-> update();
		juego-> render();

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime){
			SDL_Delay(frameDelay - frameTime);
		}


	}
	juego-> clean();

	return 0;

}*/
