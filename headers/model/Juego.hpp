#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class Juego{


public:
	Juego();
	~Juego();
	void update();
	void render();
	bool running() {return isRunning;}
private:
	void gameLoop();
	bool isRunning;

};

#endif
