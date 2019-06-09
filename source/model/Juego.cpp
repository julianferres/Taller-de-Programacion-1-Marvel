#include <Jugador.hpp>
#include <Personaje.hpp>
#include <ControladorLogger.hpp>
#include <Juego.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorTeclado.hpp>
#include <GameMenu.hpp>
#include <JuegoCliente.hpp>
#include <Equipo.hpp>
#include <string>
#include<iostream>

using namespace std;

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;


Juego::Juego(){

	this->teclado = new ControladorTeclado();
	this-> parallax = new Parallax();
	controladorLogger->registrarEvento("INFO", "Juego::Se inicio el juego");

}

Juego::~Juego(){
	delete teclado;
	delete parallax;
	delete equipo1;
	delete equipo2;

}

Equipo* Juego::getEquipo1(){
	return this->equipo1;
}

Equipo* Juego::getEquipo2(){
	return this->equipo2;
}

void Juego::crearJugador(std::string nombre,int cliente){
	int posicionXinicial;
	SDL_RendererFlip flip;
	bool ladoDerecho;
	bool equipo1;
	switch(controladorJson->cantidadClientes()){
		case 4:
			equipo1= cliente<3;
			break;
		case 3:
			equipo1 = cliente == 1 || cliente ==11;
			break;
		case 2:
			equipo1 = cliente == 1 || cliente ==11;
			break;
		case 1:
			equipo1= cliente<3;
	}
	if(equipo1){//sos del equipo1
		posicionXinicial = controladorJson->getPosicionXInicialEquipo1();
		flip = SDL_FLIP_NONE;
		ladoDerecho = false;
		controladorLogger->registrarEvento("INFO","Juego::Jugador "+to_string(cliente) +" al equipo 1");
		//cliente =1;
	}
	else{//sos del equipo 2
		posicionXinicial = controladorJson->getPosicionXInicialEquipo2();
		flip = SDL_FLIP_HORIZONTAL;
		ladoDerecho = true;
		controladorLogger->registrarEvento("INFO","Juego::Jugador "+to_string(cliente)+" al equipo 2");
		//cliente = 2;
	}

	Jugador *jugador = new Jugador(nombre,posicionXinicial,flip,ladoDerecho, cliente);
	jugadores[cliente-1]=jugador;
}

void Juego::crearEquipos(){
	if (controladorJson->cantidadClientes() == 4 || controladorJson->cantidadClientes() == 1){
		this->equipo1 = new Equipo(jugadores[0],jugadores[1]);
		this->equipo2 = new Equipo(jugadores[2],jugadores[3]);
	}
	else if (controladorJson->cantidadClientes()== 2){
		this->equipo1 = new Equipo(jugadores[0],jugadores[10]);
		this->equipo2 = new Equipo(jugadores[1],jugadores[11]);
	}
	else if (controladorJson->cantidadClientes()== 3){
		this->equipo1 = new Equipo(jugadores[0],jugadores[10]);
		this->equipo2 = new Equipo(jugadores[1],jugadores[2]);
	}

	this->jugadorActualEquipo1 = equipo1->JugadorActual();
	this->jugadorActualEquipo2 = equipo2->JugadorActual();
}

bool Juego::compare_zindexs(std::tuple<Jugador *, int> zindex1, std::tuple<Jugador *, int> zindex2){
		return (std::get<1>(zindex1) <= std::get<1>(zindex2));
}

std::vector<std::tuple<Jugador *, int>> Juego::obtenerOrdenDibujo(){
	std::vector<std::tuple<Jugador *, int>> zindexs_personajes;
	this->jugadorActualEquipo1 = equipo1->JugadorActual();
	this->jugadorActualEquipo2 = equipo2->JugadorActual();
	zindexs_personajes.push_back(std::make_tuple(jugadorActualEquipo1, jugadorActualEquipo1->devolverPersonajeActual()->zindexPersonaje()));
	zindexs_personajes.push_back(std::make_tuple(jugadorActualEquipo2, jugadorActualEquipo2->devolverPersonajeActual()->zindexPersonaje()));

	std::sort(zindexs_personajes.begin(), zindexs_personajes.end(), Juego::compare_zindexs);
	return zindexs_personajes;
}


vector<tuple<string,SDL_Rect, SDL_Rect ,SDL_RendererFlip >>Juego::dibujar(){
	SDL_RendererFlip flip ;
	vector<tuple<string,SDL_Rect , SDL_Rect,SDL_RendererFlip >> dibujables;
	vector<tuple<Jugador *, int>> zindexs_personajes = obtenerOrdenDibujo();
	vector<int>zindexes = controladorJson->getZindexes();
	this->verificarCambioDeLado();
	int fondos_dibujados = 0;
	int personajes_dibujados = 0;
	get<0>(zindexs_personajes[0])->devolverPersonajeActual()->actualizar();
	get<0>(zindexs_personajes[1])->devolverPersonajeActual()->actualizar();
	while(fondos_dibujados + personajes_dibujados < 5){
		if(fondos_dibujados == 3 || get<1>(zindexs_personajes[personajes_dibujados]) <= zindexes[fondos_dibujados]){
			Jugador * jugador = get<0>(zindexs_personajes[personajes_dibujados]);
			SDL_Rect origen = jugador->devolverPersonajeActual()->obtenerSprite()->rectOrigen();
			SDL_Rect destino = jugador->devolverPersonajeActual()->obtenerRectangulo();
			flip =  jugador->devolverPersonajeActual()->getFlip();
			dibujables.push_back(make_tuple(jugador->nombreJugador(),origen,destino,flip));
			personajes_dibujados++;
		}
		else{
			flip = SDL_FLIP_NONE;
			if(fondos_dibujados == 0 ){
				SDL_Rect* origen = parallax->camaraz1();
				SDL_Rect* destinoz1 = parallax->getDestinoZ1();
				dibujables.push_back(make_tuple(to_string(zindexes[2]),*origen,*destinoz1,flip));
			}
			else if(fondos_dibujados == 1 ){
				SDL_Rect *origen = parallax->camaraz2();
				SDL_Rect* destinoz2 = parallax->getDestinoZ2();
				dibujables.push_back(make_tuple(to_string(zindexes[1]),*origen,*destinoz2,flip));
			}
			else if(fondos_dibujados == 2 ){
				SDL_Rect *origen = parallax->camaraz3();
				SDL_Rect* destinoz3 = parallax->getDestinoZ3();
				dibujables.push_back(make_tuple(to_string(zindexes[0]),*origen,*destinoz3,flip));
			}
			fondos_dibujados++;
		}
	}
	return dibujables;

}

void Juego::verificarCambioDeLado(){
	if (this->jugadorActualEquipo1->estaDelladoDerecho()){
		if (this->jugadorActualEquipo1->posicionActual() < this->jugadorActualEquipo2->posicionActual()){
			this->equipo1->cambiarDeLado();
			this->equipo2->cambiarDeLado();
		}
	}
	else{
		if (this->jugadorActualEquipo2->posicionActual() < this->jugadorActualEquipo1->posicionActual()){
			this->equipo2->cambiarDeLado();
			this->equipo1->cambiarDeLado();
		}
	}
}

void Juego::actualizarConexion(int idCliente){
	this->equipo1->actualizarConexion(idCliente);
	this->equipo2->actualizarConexion(idCliente);
}

void Juego::teclear(SDL_Event evento, int idCliente){
	Personaje* personaje1 = jugadorActualEquipo1->devolverPersonajeActual();
	Personaje* personaje2 = jugadorActualEquipo2->devolverPersonajeActual();
	bool finEscenarioDerecha = parallax->finDeEscenarioDerecha();
	bool finEscenarioIzquierda = parallax->finDeEscenarioIzquierda();
	teclado->reiniciar();


	if (evento.window.event == SDL_WINDOWEVENT_RESIZED){
		//cliente->graficos()->maximizarVentana(evento.window.data1, evento.window.data2);
		this->equipo1->actualizarPiso();
		this->equipo1->actualizarPiso();
	}

	 switch( evento.type ){
		 case SDL_KEYDOWN:
			 teclado->eventoPresionarTecla(evento);
			 break;
		 case SDL_KEYUP:
			 teclado->eventoSoltarTecla(evento);
			 break;
	 }
	 bool puedoMoverPersonaje1 = jugadorActualEquipo1->obtenerId() == idCliente || (equipo1->TecladoHabilitado() && (equipo1->obtenerIdJugadorActual() == idCliente || equipo1->obtenerIdCompaniero() == idCliente));
	 bool puedoMoverPersonaje2 = jugadorActualEquipo2->obtenerId() == idCliente || (equipo2->TecladoHabilitado() && (equipo2->obtenerIdJugadorActual() == idCliente || equipo2->obtenerIdCompaniero() == idCliente));

	 if(puedoMoverPersonaje1 || controladorJson->cantidadClientes() == 1){
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

			if(teclado->sePresionoUnaTecla(SDL_SCANCODE_W)){
				personaje1->saltar();
				controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 salta");
			}
			if(teclado->sePresionoUnaTecla(SDL_SCANCODE_J)){
				//controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 salta");
				personaje1->golpe("golpeS");
			}
			if(teclado->sePresionoUnaTecla(SDL_SCANCODE_K)){
				personaje1->golpe("patadaS");
			}
			if(teclado->sePresionoUnaTecla(SDL_SCANCODE_U)){
				personaje1->golpe("golpeF");
			}
			if(teclado->sePresionoUnaTecla(SDL_SCANCODE_I)){
				personaje1->golpe("patadaF");
			}
			if(teclado->sePresionoUnaTecla(SDL_SCANCODE_L)){
				personaje1->defenderse();
			}
			if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_S)){
				personaje1->agacharse();
				controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 agachado");
			}
			if (teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_S)&&teclado->sePresionoUnaTecla(SDL_SCANCODE_J)){
				personaje1->golpe("golpeAS");
			}
			if (teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_S)&&teclado->sePresionoUnaTecla(SDL_SCANCODE_K)){
				personaje1->golpe("patadaAS");
			}
			if (teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_S)&&teclado->sePresionoUnaTecla(SDL_SCANCODE_U)){
				personaje1->golpe("golpeAF");
			}
			if (teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_S)&&teclado->sePresionoUnaTecla(SDL_SCANCODE_I)){
				personaje1->golpe("patadaAS");
			}
			if(teclado->seSoltoUnaTecla(SDL_SCANCODE_S) ||teclado->seSoltoUnaTecla(SDL_SCANCODE_D)|| teclado->seSoltoUnaTecla(SDL_SCANCODE_A) ){
					personaje1->cambiarAnimacion("quieto");
			}

			if(teclado->sePresionoUnaTecla(SDL_SCANCODE_E) ){
				this->equipo1->cambiarJugador();
				controladorLogger->registrarEvento("DEBUG", "Juego::Cambio de jugador del equipo 1");
			}
	 }
	 if(puedoMoverPersonaje2 || controladorJson->cantidadClientes() == 1){
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

				if(teclado->sePresionoUnaTecla(SDL_SCANCODE_UP)){
					personaje2->saltar();
					controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 salta");
				}

				if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_DOWN)){
					personaje2->agacharse();
					controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 agachado");
				}
				if (teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_DOWN)&&teclado->sePresionoUnaTecla(SDL_SCANCODE_A)){
					personaje2->golpe("golpeAS");
				}
				if (teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_DOWN)&&teclado->sePresionoUnaTecla(SDL_SCANCODE_S)){
					personaje2->golpe("patadaAS");
				}
				if(teclado->sePresionoUnaTecla(SDL_SCANCODE_Z)){
					personaje2->golpe("golpeS");
				}
				if(teclado->sePresionoUnaTecla(SDL_SCANCODE_X)){
					personaje2->golpe("patadaS");
				}
				if(teclado->sePresionoUnaTecla(SDL_SCANCODE_C)){
					//cout<<"golpe fuerte"<<endl;
				}
				if(teclado->sePresionoUnaTecla(SDL_SCANCODE_V)){
					//cout<<"patada fuerte"<<endl;
				}

				if(teclado->seSoltoUnaTecla(SDL_SCANCODE_DOWN) || teclado->seSoltoUnaTecla(SDL_SCANCODE_LEFT) || teclado->seSoltoUnaTecla(SDL_SCANCODE_RIGHT)){
						personaje2->cambiarAnimacion("quieto");
				}

				if(teclado->sePresionoUnaTecla(SDL_SCANCODE_M)  ){
					this->equipo2->cambiarJugador();
					controladorLogger->registrarEvento("DEBUG", "Juego::Cambio de jugador del equipo 2");
				}


	 }
	 if(teclado->sePresionoUnaTecla(SDL_SCANCODE_F11)){
		 //cliente->graficos()->cambiarPantallaCompleta();
		 controladorLogger->registrarEvento("DEBUG", "Se cambia a pantalla completa");
	 }

}

std::vector<std::string> Juego::gameMenu(){
	std::vector<std::string> nombres_jugadores;
	nombres_jugadores.push_back("Venom");
	nombres_jugadores.push_back("Spiderman");
	nombres_jugadores.push_back("Venom");
	nombres_jugadores.push_back("Hulk");
	return nombres_jugadores;
}
