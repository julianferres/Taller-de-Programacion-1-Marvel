#include <Jugador.hpp>
#include <Personaje.hpp>
#include <ControladorLogger.hpp>
#include <Juego.hpp>
#include <SpriteAnimado.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

Juego::Juego(){
	int posicionMoverFondoIzq = controladorJson->anchoVentana() * 1/8;
	int posicionMoverFondoDer = controladorJson->anchoVentana() * 7/8;

	this->isRunning=true;
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop(posicionMoverFondoIzq, posicionMoverFondoDer);
}

Juego::~Juego()
{}

void Juego::gameLoop(int posicionMoverFondoIzq, int posicionMoverFondoDer){

	ControladorGrafico graficos;
	SDL_Event evento;

	this->dibujarFondo(graficos);
	SDL_RendererFlip flip1 = SDL_FLIP_NONE;
	SDL_RendererFlip flip2 = SDL_FLIP_HORIZONTAL;
	this->jugador1 = new Jugador(graficos,"CapitanAmerica", "Venom",controladorJson->anchoVentana()/8,flip1);
	this->jugador2 = new Jugador(graficos,"Spiderman", "CapitanAmerica",controladorJson->anchoVentana()*3/4, flip2);

	while (isRunning){
		startTime = SDL_GetTicks();
		this->teclear(graficos, evento, posicionMoverFondoIzq, posicionMoverFondoDer);
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

void Juego::teclear(ControladorGrafico &grafico, SDL_Event evento,int posicionMoverFondoIzq, int posicionMoverFondoDer){
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	Personaje* personaje1 = jugador1->devolverPersonajeActual();
	Personaje* personaje2 = jugador2->devolverPersonajeActual();
	while(SDL_PollEvent(&evento)){
			if (evento.type == SDL_QUIT  || keys[SDL_SCANCODE_ESCAPE] ){
				isRunning = false;
		        break;
		    }
			if (evento.type == SDL_KEYDOWN){
				if(evento.key.keysym.sym == SDLK_l){
					this->jugador1->cambiarPersonaje();
					controladorLogger->registrarEvento("DEBUG", "Cambio de personaje del jugador 1");
					break;
				}
				if(evento.key.keysym.sym == SDLK_o){
					this->jugador2->cambiarPersonaje();
					controladorLogger->registrarEvento("DEBUG", "Cambio de personaje del jugador 2");
					break;
				}
			}
			//Jugador 1
			 if (keys[SDL_SCANCODE_D]){
				if(! personaje1->colisionaAlaDerecha(personaje2->obtenerRectangulo() ) ){
					this->jugador1->personajeActualMoverDerecha();
					if(jugador1->obtenerPosicionXPersonaje(true) > posicionMoverFondoDer) this->parallax->MoverCamaraDerecha();
					controladorLogger->registrarEvento("DEBUG", "Jugador 1 a la derecha");
				}

			}
			if (keys[SDL_SCANCODE_A]){
				if(! personaje1->colisionaAlaIzquierda(personaje2->obtenerRectangulo() )){
					this->jugador1->personajeActualMoverIzquierda();
					if (jugador1->obtenerPosicionXPersonaje(false) < posicionMoverFondoIzq) this->parallax->MoverCamaraIzquierda();
					controladorLogger->registrarEvento("DEBUG", "Jugador 1 a la izquierda");
				}
			}
			if (keys[SDL_SCANCODE_S]){
				this->jugador1->personajeActualAgacharse();
				controladorLogger->registrarEvento("DEBUG", "Jugador 1 agachado");
			}
			if (keys[SDL_SCANCODE_W]){
				this->jugador1->personajeActualSaltar();
				controladorLogger->registrarEvento("DEBUG", "Jugador 1 salta");
			}
			//Jugador2
		   if (keys[SDL_SCANCODE_RIGHT]){
			   if(! personaje2->colisionaAlaDerecha(personaje1->obtenerRectangulo())){
					this->jugador2->personajeActualMoverDerecha();
					if(jugador2->obtenerPosicionXPersonaje(true) > posicionMoverFondoDer) this->parallax->MoverCamaraDerecha();
					controladorLogger->registrarEvento("DEBUG", "Jugador 2 a la derecha");
			   }
		    }
		    if (keys[SDL_SCANCODE_LEFT]){
		    	if(! personaje2->colisionaAlaIzquierda(personaje1->obtenerRectangulo())){
		    		this->jugador2->personajeActualMoverIzquierda();
					if (jugador2->obtenerPosicionXPersonaje(false) < posicionMoverFondoIzq) this->parallax->MoverCamaraIzquierda();
					controladorLogger->registrarEvento("DEBUG", "Jugador 2 a la izquierda");
		    	}
		    }
		    if (keys[SDL_SCANCODE_UP]){
		    	this->jugador2->personajeActualSaltar();
		    	controladorLogger->registrarEvento("DEBUG", "Jugador 2 salta");
		    }
		    if (keys[SDL_SCANCODE_DOWN]){
		    	this->jugador2->personajeActualAgacharse();
				controladorLogger->registrarEvento("DEBUG", "Jugador 2 agachado");
			}
	}
}
