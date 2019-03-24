#include <ControladorTexturas.h>
#include <Juego.hpp>
#include <Personaje.h>
#include <ControladorGrafico.hpp>

Personaje* jugador1 ;
Personaje* jugador2;

SDL_Renderer* Juego::renderer = nullptr;

Juego::Juego()
{}

Juego::~Juego()
{}

void Juego::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
	ControladorGrafico graficos;
	int flags = 0;

	if(fullscreen){
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING)==0){

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window,-1,0);
		if(renderer){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
		std::cout << "Juego iniciado!" << std::endl;
	}
	else{
		isRunning = false;
	}


	jugador1 = new Personaje(graficos,0,300);
	jugador2 = new Personaje(graficos,500,300);

}

void Juego::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_s:
					std::cout << "Me agacho!" << std::endl;
					break;
				case SDLK_w:
						std::cout << "Salto!" << std::endl;
						break;
				case SDLK_d:
						std::cout << "Jugador 1 a la derecha!" << std::endl;
						jugador1->MoverDerecha();
						break;
				case SDLK_a:
						std::cout << "Jugador 1 a la izquierda!" << std::endl;
						jugador1->MoverIzquierda();
						break;
				case SDLK_LEFT:
						std::cout << "Jugador 2 a la izquierda!" << std::endl;
						jugador2->MoverIzquierda();
						break;
			}
			break;
		default:
			break;
	}

}

void Juego::update(float tiempoTranscurrido)
{
	jugador1->update(tiempoTranscurrido);
	jugador2->update(tiempoTranscurrido);
}

void Juego::dibujar(ControladorGrafico graficos)
{
	graficos.clear();
	//SDL_RenderClear(renderer);
	jugador1-> dibujar(graficos);
	jugador2->dibujar(graficos);
	//SDL_RenderPresent(renderer);
	graficos.render();
}

void Juego::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Juego finalizado!" << std::endl;
}
//testPersonaje




