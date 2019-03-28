#include <ControladorGrafico.hpp>
#include <ControladorTeclado.hpp>
#include <Juego.hpp>
#include <Sprite.hpp>

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
	this->imagen=Sprite(graficos,"contents/images/CaptainAmericaSprites.png",7,20,89,115,1,2000);
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
		this->dibujar(graficos);
	}
}


void Juego::actualizar(float tiempo){
}

void Juego::dibujar(ControladorGrafico &grafico){
	grafico.limpiar();
	this->imagen.dibujar(grafico,1,200);
	grafico.render();
}






