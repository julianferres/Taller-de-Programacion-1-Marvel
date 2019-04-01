#include <ControladorGrafico.hpp>
#include <ControladorTeclado.hpp>
#include <ControladorLogger.hpp>
#include <Personaje.hpp>
#include <Juego.hpp>

extern ControladorLogger *controladorLogger;

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
	if(this->parallax == NULL)
		controladorLogger->registrarEvento("ERROR", "No se pudo cargar el parallax");
	else
		controladorLogger->registrarEvento("DEBUG", "Se cargo correctamente el parallax");


	this->personaje=new Personaje(graficos,"contents/images/CaptainAmericaSprites.png",0,400);
	controladorLogger->registrarEvento("INFO", "Se cargo correctamente la imagen del personaje 1");
	controladorLogger->registrarEvento("INFO", "Juego iniciado");

	SDL_Event evento;
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
				controladorLogger->registrarEvento("INFO", "Juego finalizado");
				break;
			}
		}
		if(teclado.wasKeyPressed(SDL_SCANCODE_ESCAPE)==true){
			return;
		}
		else if(teclado.wasKeyPressed(SDL_SCANCODE_RIGHT)==true){
			this->personaje->MoverDerecha();
			this->parallax->MoverCamaraDerecha();
			controladorLogger->registrarEvento("DEBUG", "Jugador 1 a la derecha");
		}
		else if(teclado.wasKeyPressed(SDL_SCANCODE_LEFT)==true){
					this->personaje->MoverIzquierda();
					this->parallax->MoverCamaraIzquierda();
					controladorLogger->registrarEvento("DEBUG", "Jugador 1 a la izquierda");
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
	this->personaje->dibujar(grafico);
	grafico.render();
}






