#include <Jugador.hpp>
#include <Personaje.hpp>
#include <ControladorLogger.hpp>
#include <Juego.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorTeclado.hpp>
#include <GameMenu.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;


Juego::Juego(){

	SDL_Init(0);
	SDL_VideoInit(NULL);
	SDL_InitSubSystem(SDL_INIT_TIMER);

	this->startTime = SDL_GetTicks();
	this->graficos = new ControladorGrafico();
	this->startGameMenu();
	this->teclado = new ControladorTeclado();
	this-> parallax = new Parallax(*graficos);
	this->iniciarFondo();
	this->jugador1 = new Jugador(*graficos,controladorJson->jugador1Personaje(0), controladorJson->jugador1Personaje(1),controladorJson->getPosicionXInicialJugador1(),SDL_FLIP_NONE, false);
	this->jugador2 = new Jugador(*graficos,controladorJson->jugador2Personaje(0), controladorJson->jugador2Personaje(1),controladorJson->getPosicionXInicialJugador2(), SDL_FLIP_HORIZONTAL, true);
	controladorLogger->registrarEvento("INFO", "Juego::Se iniciaron los jugadores");
	this->isRunning=true;
	this->gameLoop();

}

Juego::~Juego(){
	delete teclado;
	delete parallax;
	delete jugador1;
	delete jugador2;
	delete graficos;
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_VideoQuit();
	SDL_QuitSubSystem(SDL_INIT_TIMER);
	SDL_Quit();
}

void Juego::startGameMenu(){
	controladorLogger->registrarEvento("DEBUG", "Juego::Inicio menu");
	GameMenu *menu = new GameMenu(*graficos);
	delete menu;
}

void Juego::gameLoop(){

	while (isRunning){
		this->startTime = SDL_GetTicks();
		this->teclear();
		this->dibujar();
		if(SDL_GetTicks() - startTime < MAX_FRAME_TIME)
			SDL_Delay( MAX_FRAME_TIME - SDL_GetTicks() +startTime );

	}
}

void Juego::iniciarFondo(){
	if(this->parallax == NULL)
		controladorLogger->registrarEvento("ERROR", "Juego::No se pudo cargar el parallax");
	else
		controladorLogger->registrarEvento("INFO", "Juego::Se cargo correctamente el parallax");
}

bool Juego::compare_zindexs(std::tuple<Jugador *, int> zindex1, std::tuple<Jugador *, int> zindex2){
		return (std::get<1>(zindex1) <= std::get<1>(zindex2));
}

std::vector<std::tuple<Jugador *, int>> Juego::obtenerOrdenDibujo(){
	std::vector<std::tuple<Jugador *, int>> zindexs_personajes;

	zindexs_personajes.push_back(std::make_tuple(jugador1, jugador1->devolverPersonajeActual()->zindexPersonaje()));
	zindexs_personajes.push_back(std::make_tuple(jugador2, jugador2->devolverPersonajeActual()->zindexPersonaje()));

	std::sort(zindexs_personajes.begin(), zindexs_personajes.end(), Juego::compare_zindexs);
	return zindexs_personajes;
}

void Juego::dibujar(){
	graficos->limpiar();
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	std::vector<std::tuple<Jugador *, int>> zindexs_personajes = obtenerOrdenDibujo();
	std::vector<int> zindexs_fondos = parallax->getzindexes();

	this->verificarCambioDeLado();

	int fondos_dibujados = 0;
	int personajes_dibujados = 0;
	while(fondos_dibujados + personajes_dibujados < 5){
		if(fondos_dibujados == 3 && personajes_dibujados < 2){
			get<0>(zindexs_personajes[personajes_dibujados])->personajeActualDibujar(*graficos);
			personajes_dibujados++;
		}

		else if ((personajes_dibujados < 2) && get<1>(zindexs_personajes[personajes_dibujados]) <= zindexs_fondos[fondos_dibujados]){
			get<0>(zindexs_personajes[personajes_dibujados])->personajeActualDibujar(*graficos);
			personajes_dibujados++;
		}
		else{
			if(fondos_dibujados == 0 && parallax->backgroundz1()){
				graficos->dibujarImagen(parallax->backgroundz1(), parallax->camaraz1(), NULL, flip);
			}

			else if(fondos_dibujados == 1 && parallax->backgroundz2())
				graficos->dibujarImagen(parallax->backgroundz2(), parallax->camaraz2(), NULL, flip);


			else if(fondos_dibujados == 2 && parallax->backgroundz3()){
				graficos->dibujarImagen(parallax->backgroundz3(), parallax->camaraz3() , NULL, flip);
			}
			fondos_dibujados++;

		}
	}

	graficos->render();
}

void Juego::verificarCambioDeLado(){
	if (this->jugador1->estaDelladoDerecho()){
		if (this->jugador1->posicionActual() < this->jugador2->posicionActual()){
			this->jugador1->cambiarDeLado();
			this->jugador2->cambiarDeLado();
		}
	}else{
		if (this->jugador2->posicionActual() < this->jugador1->posicionActual()){
			this->jugador2->cambiarDeLado();
			this->jugador1->cambiarDeLado();
		}
	}
}


void Juego::teclear(){
	SDL_Event evento;
	Personaje* personaje1 = jugador1->devolverPersonajeActual();
	Personaje* personaje2 = jugador2->devolverPersonajeActual();
	bool finEscenarioDerecha = parallax->finDeEscenarioDerecha();
	bool finEscenarioIzquierda = parallax->finDeEscenarioIzquierda();
	teclado->reiniciar();

	while(SDL_PollEvent(&evento)){
		if (evento.type == SDL_QUIT   ){
			isRunning = false;
			break;
		}

		if (evento.window.event == SDL_WINDOWEVENT_RESIZED){
			graficos->maximizarVentana(evento.window.data1, evento.window.data2);
			this->jugador1->actualizarPiso();
			this->jugador2->actualizarPiso();
		}

		 switch( evento.type ){
		 	 case SDL_KEYDOWN:
		 		 teclado->eventoPresionarTecla(evento);
		 		 break;
		 	 case SDL_KEYUP:
		 		 teclado->eventoSoltarTecla(evento);
		 		 break;
		 }
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_D)){
		 if(personaje1->moverDerecha(personaje2,finEscenarioDerecha)){
			 this->parallax->moverCamaraDerecha();
			 /*if(! personaje1->colisionaAlaDerecha(personaje2->obtenerRectangulo() )  ){
					if(personaje1->MoverDerecha(personaje2,finEscenarioDerecha))
						this->parallax->MoverCamaraDerecha();
					controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 a la derecha");
				}*/
		 }
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_A)){
		if (personaje1->moverIzquierda(personaje2,finEscenarioIzquierda)){
			this->parallax->moverCamaraIzquierda();
			/*if(! personaje1->colisionaAlaIzquierda(personaje2->obtenerRectangulo() )  ){
					if (personaje1->MoverIzquierda(personaje2,finEscenarioIzquierda))
						this->parallax->MoverCamaraIzquierda();
					controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 a la izquierda");
				}*/
		}
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_W)){
		personaje1->saltar();
		controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 salta");
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_S)){
		personaje1->agacharse();
		controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 agachado");
	}

	if(teclado->sePresionoUnaTecla(SDL_SCANCODE_E) ){
			this->jugador1->cambiarPersonaje();
			controladorLogger->registrarEvento("DEBUG", "Juego::Cambio de personaje del jugador 1");
		}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_LEFT)){
		if (personaje2->moverIzquierda(personaje1,finEscenarioIzquierda)){
			this->parallax->moverCamaraIzquierda();
			/*if(! personaje2->colisionaAlaIzquierda(personaje1->obtenerRectangulo()) ){
				if (personaje2->MoverIzquierda(personaje1,finEscenarioIzquierda)){
					this->parallax->MoverCamaraIzquierda();
				}
			controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 a la izquierda");
			}*/
		}
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_RIGHT)){
	   if(personaje2->moverDerecha(personaje1, finEscenarioDerecha) ){
		   this->parallax->moverCamaraDerecha();
			  /* if(! personaje2->colisionaAlaDerecha(personaje1->obtenerRectangulo()) ){
					if(personaje2->MoverDerecha(personaje1, finEscenarioDerecha) )
						this->parallax->MoverCamaraDerecha();
					controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 a la derecha");
			   }*/
	   }
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_UP)){
		personaje2->saltar();
		controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 salta");
	}

	if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_DOWN)){
		personaje2->agacharse();
		controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 agachado");
	}

	if(teclado->sePresionoUnaTecla(SDL_SCANCODE_M)  ){
		this->jugador2->cambiarPersonaje();
		controladorLogger->registrarEvento("DEBUG", "Juego::Cambio de personaje del jugador 2");
	}

	if(teclado->sePresionoUnaTecla(SDL_SCANCODE_F11)){
		graficos->cambiarPantallaCompleta();
		controladorLogger->registrarEvento("DEBUG", "Se cambia a pantalla completa");
	}

	if(teclado->sePresionoUnaTecla(SDL_SCANCODE_ESCAPE)){
		isRunning=false;
	}


}
