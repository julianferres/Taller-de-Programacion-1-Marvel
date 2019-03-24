#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <Personaje.hpp>


class ControladorGrafico;

class Juego{


public:
	Juego();
	~Juego();

//void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen );
	//void handleEvents();
	//void update(float tiempoTranscurrido);
	//void dibujar(ControladorGrafico graficos);
	//void clean();
	bool running() {return isRunning;}

	//static SDL_Renderer *renderer;
//	static SDL_Event event;

private:
	void dibujar(ControladorGrafico &graficos);
	void gameLoop();
	void handleEvents();
//	void dibujar(ControladorGrafico &graficos);
	void update(float elapsedTime);
	void iniciarJugadores(ControladorGrafico &graficos);
	void iniciarPantalla(ControladorGrafico &graficos);
	void atraparEventos();



//	int cnt = 0;
	bool isRunning;
	bool _fullScreen = false;
	//SDL_Window *window;

};
//hola
#endif
