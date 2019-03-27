#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <ControladorGrafico.hpp>
#include <Sprite.hpp>


class Juego{


public:
	Juego();
	~Juego();
	bool running() {return isRunning;}
private:
	void gameLoop();
	void dibujar(ControladorGrafico &grafico);
	void actualizar(float tiempo);
	bool isRunning;
	Sprite imagen;

};

#endif
