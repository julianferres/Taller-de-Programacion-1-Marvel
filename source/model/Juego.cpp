#include <Jugador.hpp>
#include <ControladorLogger.hpp>
#include <Juego.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

Juego::Juego(){
	int posicionMoverFondoIzq = controladorJson->anchoVentana() * 1/4;
	int posicionMoverFondoDer = controladorJson->anchoVentana() * 3/4;

	this->isRunning=true;
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop(posicionMoverFondoIzq, posicionMoverFondoDer);
}

Juego::~Juego()
{}

void Juego::gameLoop(int posicionMoverFondoIzq, int posicionMoverFondoDer){
	ControladorGrafico graficos;
	ControladorTeclado teclado;
	SDL_Event evento;

	this->dibujarFondo(graficos);
	this-> parallax = new Parallax(graficos);
	if(this->parallax == NULL)
		controladorLogger->registrarEvento("ERROR", "No se pudo cargar el parallax");
	else
		controladorLogger->registrarEvento("DEBUG", "Se cargo correctamente el parallax");

	this->jugador1 = new Jugador(graficos,"CapitanAmerica", "Spiderman");

	while (isRunning){
		startTime = SDL_GetTicks();
		this->teclear(evento,teclado, posicionMoverFondoIzq, posicionMoverFondoDer);
		this->dibujar(graficos);
		if(SDL_GetTicks() - startTime < MAX_FRAME_TIME)
			SDL_Delay( MAX_FRAME_TIME - SDL_GetTicks() +startTime );

	}

}
void Juego::dibujarFondo(ControladorGrafico &graficos){
	this-> parallax = new Parallax(graficos);
	if(this->parallax == NULL)
		controladorLogger->registrarEvento("ERROR", "No se pudo cargar el parallax");
	else
		controladorLogger->registrarEvento("DEBUG", "Se cargo correctamente el parallax");
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

void Juego::teclear(SDL_Event evento,ControladorTeclado teclado, int posicionMoverFondoIzq, int posicionMoverFondoDer){
	while(SDL_PollEvent(&evento)){
		switch(evento.type){
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				switch(evento.key.keysym.sym){
					case SDLK_RIGHT:
						this->jugador1->personajeActualMoverDerecha();
						//if(jugador1->obtenerPosicionXPersonaje() > posicionMoverFondoDer)
						if(jugador1->obtenerPosicionXPersonaje(true) > posicionMoverFondoDer) this->parallax->MoverCamaraDerecha();
						controladorLogger->registrarEvento("DEBUG", "una vez a la derecha");
						break;
					case SDLK_LEFT:
						this->jugador1->personajeActualMoverIzquierda();
						if (jugador1->obtenerPosicionXPersonaje(false) < posicionMoverFondoIzq) this->parallax->MoverCamaraIzquierda();
						controladorLogger->registrarEvento("DEBUG", "una vez a la izquierda");
						break;
					case SDLK_l:
						this->jugador1->cambiarPersonaje();
						controladorLogger->registrarEvento("DEBUG", "Cambio de personaje");
						break;
					case SDLK_ESCAPE:
						isRunning = false;
						break;
				}
				break;
			default:
				break;
		}
	}
}
