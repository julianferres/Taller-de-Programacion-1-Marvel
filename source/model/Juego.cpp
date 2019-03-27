#include <ControladorTexturas.h>
#include <ControladorGrafico.hpp>
#include <ControladorTeclado.hpp>
#include <Juego.hpp>
#include <Personaje.h>

Juego::Juego(){
	this->isRunning=true;
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Juego::~Juego()
{}
void Juego::gameLoop(){
	ControladorGrafico graficos;
	ControladorTeclado teclado;
	SDL_Event evento;
	while (true){
		teclado.beginNewFrame();
		if(SDL_PollEvent(&evento)){
			if(evento.type==SDL_KEYDOWN){
				if(evento.key.repeat==0){
					teclado.keyDownEvent(evento);
				}
			}
			else if(evento.type==SDL_KEYUP){
				teclado.keyUpEvent(evento);
			}
			else if(evento.type==SDL_QUIT){
				return;
			}
		}
		if(teclado.wasKeyPressed(SDL_SCANCODE_ESCAPE)==true){
			return;
		}

	}


}


void Juego::update()
{
	/*jugador1->Update();
	jugador2->Update();
	*/
}

void Juego::render()
{
	/*SDL_RenderClear(renderer);
	jugador1-> Render();
	jugador2->Render();
	SDL_RenderPresent(renderer);*/
}






