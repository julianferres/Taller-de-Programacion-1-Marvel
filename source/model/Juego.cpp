#include <ControladorGrafico.hpp>
#include <ControladorTeclado.hpp>
#include <Personaje.hpp>
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
	this->personaje=new Personaje(graficos,"contents/images/CaptainAmericaSprites.png",0,200);
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
		else if(teclado.wasKeyPressed(SDL_SCANCODE_RIGHT)==true){
			this->personaje->MoverDerecha();
			std::cout<<"una vez a la derecha"<<endl;
		}
		else if(teclado.wasKeyPressed(SDL_SCANCODE_LEFT)==true){
					this->personaje->MoverIzquierda();
					std::cout<<"una vez a la izquierda"<<endl;
				}

		this->dibujar(graficos);
	}
}


void Juego::actualizar(float tiempo){
}

void Juego::dibujar(ControladorGrafico &grafico){
	grafico.limpiar();
	this->personaje->dibujar(grafico);
	grafico.render();
}






