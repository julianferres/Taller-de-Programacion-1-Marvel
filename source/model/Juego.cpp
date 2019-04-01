#include <Jugador.hpp>
#include <ControladorLogger.hpp>
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
	SDL_Event evento;

	this->dibujarFondo(graficos);
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

void Juego::teclear(SDL_Event evento,ControladorTeclado teclado){
	while(SDL_PollEvent(&evento)){
		switch(evento.type){
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				switch(evento.key.keysym.sym){
					case SDLK_RIGHT:
						this->jugador1->personajeActualMoverDerecha();
						this->parallax->MoverCamaraDerecha();
						controladorLogger->registrarEvento("DEBUG", "una vez a la derecha");
						break;
					case SDLK_LEFT:
						this->jugador1->personajeActualMoverIzquierda();
						this->parallax->MoverCamaraIzquierda();
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
