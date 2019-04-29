#include <JuegoCliente.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <TexturasFondos.hpp>



JuegoCliente::JuegoCliente(){
	SDL_Init(0);
	SDL_VideoInit(NULL);
	SDL_InitSubSystem(SDL_INIT_TIMER);
	this->grafico = new ControladorGrafico();
	this->texturasFondos = new TexturasFondos(*grafico);
}

JuegoCliente::~JuegoCliente(){
	delete grafico;
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_VideoQuit();
	SDL_QuitSubSystem(SDL_INIT_TIMER);
	SDL_Quit();
}

ControladorGrafico* JuegoCliente::graficos(){
	return this->grafico;
}

TexturasFondos* JuegoCliente::fondos(){
	return this->texturasFondos;
}



