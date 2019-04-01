#include <ControladorGrafico.hpp>
#include <ControladorTeclado.hpp>
#include <Jugador.hpp>
#include <Juego.hpp>

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
	this-> parallax = new Parallax(graficos);
	SDL_Event evento;

	this->jugador1 = new Jugador(graficos,"contents/images/CaptainAmericaSprites.png",0,300);


	while (isRunning){
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
				isRunning = false;
				break;
			}
		}
		if(teclado.wasKeyPressed(SDL_SCANCODE_ESCAPE)==true){
			return;
		}
		else if(teclado.wasKeyPressed(SDL_SCANCODE_RIGHT)==true){
			this->jugador1->personajeActualMoverDerecha();
			this->parallax->MoverCamaraDerecha();
			std::cout<<"una vez a la derecha"<<endl;
		}
		else if(teclado.wasKeyPressed(SDL_SCANCODE_LEFT)==true){
					this->jugador1->personajeActualMoverIzquierda();
					this->parallax->MoverCamaraIzquierda();
					std::cout<<"una vez a la izquierda"<<endl;
				}
		else if(teclado.wasKeyPressed(SDL_SCANCODE_L)==true){
			this->jugador1->cambiarPersonaje();
			std::cout<<"Cambio personaje actual"<<endl;
		}
		this->dibujar(graficos);
	}

}


void Juego::actualizar(float tiempo){
}

void Juego::dibujar(ControladorGrafico &grafico){
	grafico.limpiar();
	grafico.dibujarImagen(parallax->Backgroundz1(), parallax->Camaraz1(), NULL);
	grafico.dibujarImagen(parallax->Backgroundz2(), parallax->Camaraz2(), NULL);
	grafico.dibujarImagen(parallax->Backgroundz3(), parallax->Camaraz3() , NULL);
	this->jugador1->personajeActualDibujar(grafico);
	grafico.render();
}






