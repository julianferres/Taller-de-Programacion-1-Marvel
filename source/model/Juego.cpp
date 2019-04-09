#include <Jugador.hpp>
#include <Personaje.hpp>
#include <ControladorLogger.hpp>
#include <Juego.hpp>
#include <SpriteAnimado.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

#define posicionXInicialJugador1  controladorJson->anchoVentana() * 1/4
#define   posicionXInicialJugador2  controladorJson->anchoVentana() *3/4

#define limiteFondoIzq  controladorJson->anchoVentana() * 1/8
#define limiteFondoDer  controladorJson->anchoVentana() * 15/16

Juego::Juego(){

	this->isRunning=true;
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Juego::~Juego()
{}

void Juego::gameLoop(){

	ControladorGrafico graficos;
	SDL_Event evento;

	this->dibujarFondo(graficos);
	SDL_RendererFlip flip1 = SDL_FLIP_NONE;
	SDL_RendererFlip flip2 = SDL_FLIP_HORIZONTAL;
	this->jugador1 = new Jugador(graficos,"CapitanAmerica", "Venom",posicionXInicialJugador1,flip1);
	this->jugador2 = new Jugador(graficos,"Spiderman", "MegaMan",posicionXInicialJugador2, flip2);

	while (isRunning){
		startTime = SDL_GetTicks();
		this->teclear(graficos, evento);
		this->dibujar(graficos);
		if(SDL_GetTicks() - startTime < MAX_FRAME_TIME)
			SDL_Delay( MAX_FRAME_TIME - SDL_GetTicks() +startTime );

	}

}
void Juego::dibujarFondo(ControladorGrafico &graficos){
	this-> parallax = new Parallax(graficos);
	if(this->parallax == NULL)
		controladorLogger->registrarEvento("ERROR", "Juego::No se pudo cargar el parallax");
	else
		controladorLogger->registrarEvento("DEBUG", "Juego::Se cargo correctamente el parallax");
}

void Juego::dibujar(ControladorGrafico &grafico){
	grafico.limpiar();
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	grafico.dibujarImagen(parallax->Backgroundz1(), parallax->Camaraz1(), NULL, flip);
	grafico.dibujarImagen(parallax->Backgroundz2(), parallax->Camaraz2(), NULL, flip);
	grafico.dibujarImagen(parallax->Backgroundz3(), parallax->Camaraz3() , NULL, flip);
	this->jugador1->personajeActualDibujar(grafico);
	this->jugador2->personajeActualDibujar(grafico);
	grafico.render();
}

void Juego::teclear(ControladorGrafico &grafico, SDL_Event evento){
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	Personaje* personaje1 = jugador1->devolverPersonajeActual();
	Personaje* personaje2 = jugador2->devolverPersonajeActual();
	bool finEscenarioDerecha = parallax->finDeEscenarioDerecha();
	bool finEscenarioIzquierda = parallax->finDeEscenarioIzquierda();
	while(SDL_PollEvent(&evento)){
			if (evento.type == SDL_QUIT  || keys[SDL_SCANCODE_ESCAPE] ){
				isRunning = false;
		        break;
		    }
			if (evento.type == SDL_KEYDOWN){
				if(evento.key.keysym.sym == SDLK_l){
					this->jugador1->cambiarPersonaje();
					controladorLogger->registrarEvento("DEBUG", "Juego::Cambio de personaje del jugador 1");
					break;
				}
				if(evento.key.keysym.sym == SDLK_o){
					this->jugador2->cambiarPersonaje();
					controladorLogger->registrarEvento("DEBUG", "Juego::Cambio de personaje del jugador 2");
					break;
				}
			}
			//Jugador 1
			 if (keys[SDL_SCANCODE_D]){
				if(! personaje1->colisionaAlaDerecha(personaje2->obtenerRectangulo() )  ){
					if(personaje1->MoverDerecha(personaje2,finEscenarioDerecha))
						this->parallax->MoverCamaraDerecha();
					controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 a la derecha");
				}
			}
			if (keys[SDL_SCANCODE_A]){
				if(! personaje1->colisionaAlaIzquierda(personaje2->obtenerRectangulo() )  ){
					if (personaje1->MoverIzquierda(personaje2,finEscenarioIzquierda))
						this->parallax->MoverCamaraIzquierda();
					controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 a la izquierda");
				}
			}
			if (keys[SDL_SCANCODE_S]){
				personaje1->agacharse();
				controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 agachado");
			}
			if (keys[SDL_SCANCODE_W]){
				personaje1->Saltar();
				controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 salta");
			}
			//Jugador2
		   if (keys[SDL_SCANCODE_RIGHT]){
			   if(! personaje2->colisionaAlaDerecha(personaje1->obtenerRectangulo()) ){
					if(personaje2->MoverDerecha(personaje1, finEscenarioDerecha) )
						this->parallax->MoverCamaraDerecha();
					controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 a la derecha");
			   }
		    }
		    if (keys[SDL_SCANCODE_LEFT]){
		    	if(! personaje2->colisionaAlaIzquierda(personaje1->obtenerRectangulo()) ){
		    		if (personaje2->MoverIzquierda(personaje1,finEscenarioIzquierda))
		    			this->parallax->MoverCamaraIzquierda();
					controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 a la izquierda");
		    	}
		    }
		    if (keys[SDL_SCANCODE_UP]){
		    	personaje2->Saltar();
		    	controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 salta");
		    }
		    if (keys[SDL_SCANCODE_DOWN]){
		    	personaje2->agacharse();
				controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 agachado");
			}
	}
}
