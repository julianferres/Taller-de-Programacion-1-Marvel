#include <Jugador.hpp>
#include <ControladorLogger.hpp>
#include <Juego.hpp>

extern ControladorLogger *controladorLogger;
const int FPS = 50;
const int MAX_FRAME_TIME = 5 * 1000 / FPS;
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

	this-> parallax = new Parallax(graficos);
	if(this->parallax == NULL)
		controladorLogger->registrarEvento("ERROR", "No se pudo cargar el parallax");
	else
		controladorLogger->registrarEvento("DEBUG", "Se cargo correctamente el parallax");

	this->jugador1 = new Jugador(graficos,"CapitanAmerica", "Spiderman");
	int LAST_UPDATE_TIME = SDL_GetTicks();
	while (isRunning){
		this->teclear(evento,teclado);
		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->actualizar(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->dibujar(graficos);
	}

}


void Juego::actualizar(float tiempo){
	//this->jugador1.actualizar(tiempo);
}

void Juego::dibujar(ControladorGrafico &grafico){
	grafico.limpiar();
	grafico.dibujarImagen(parallax->Backgroundz1(), parallax->Camaraz1(), NULL);
	grafico.dibujarImagen(parallax->Backgroundz2(), parallax->Camaraz2(), NULL);
	grafico.dibujarImagen(parallax->Backgroundz3(), parallax->Camaraz3() , NULL);
	this->jugador1->personajeActualDibujar(grafico);
	grafico.render();
}

void Juego::teclear(SDL_Event evento,ControladorTeclado teclado){
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
		}
	}
	if(teclado.wasKeyPressed(SDL_SCANCODE_ESCAPE)==true){
		isRunning = false;
	}
	else if(teclado.wasKeyPressed(SDL_SCANCODE_RIGHT)==true){
		this->jugador1->personajeActualMoverDerecha();
		this->parallax->MoverCamaraDerecha();
		controladorLogger->registrarEvento("DEBUG", "una vez a la derecha");
	}
	else if(teclado.wasKeyPressed(SDL_SCANCODE_LEFT)==true){
		this->jugador1->personajeActualMoverIzquierda();
		this->parallax->MoverCamaraIzquierda();
		controladorLogger->registrarEvento("DEBUG", "una vez a la izquierda");
	}
	else if(teclado.wasKeyPressed(SDL_SCANCODE_L)==true){
		this->jugador1->cambiarPersonaje();
		controladorLogger->registrarEvento("DEBUG", "Cambio de personaje");
	}
}
//update





