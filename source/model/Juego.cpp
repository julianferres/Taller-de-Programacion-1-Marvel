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
	//TODO Parallax parametro round
	this->isRunning = true;
	this->teclado = new ControladorTeclado();
	this->roundActual = new Round(1);
	this-> parallax = this->roundActual->getParallax();
	this->controladorColisiones = new ControladorColisiones();
	controladorLogger->registrarEvento("INFO", "Juego::Se inicio el juego");

}

Juego::~Juego(){
	delete teclado;
	delete parallax;
	delete equipo1;
	delete equipo2;

}

void Juego::nuevoRound(){
	this->ganadores.push_back(this->getGanadorUltimoRound());
	this->reiniciarPersonajes();
	int nuevoNum = this->roundActual->getNumero()+1;
	if (nuevoNum == 4){//TODO Cuando se sepa el ganador posta, esto cambia si un mimo equipo gana los dos primeros rounds
		isRunning = false;
		return;
	}
	this->roundActual = new Round(nuevoNum);
}
void Juego::iniciarRound(){
	this->roundActual->iniciarTiempo();
}

bool Juego::roundFinalizado(){
	return this->roundActual->finalizado();
}
void Juego::actualizarTiempo(){
	this->roundActual->actualizarTiempo();
}

int Juego::numeroRound(){
	return this->roundActual->getNumero();
}

bool Juego::running(){
	return this->isRunning;
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

std::vector<std::tuple<std::string,SDL_Rect , SDL_Rect,SDL_RendererFlip>> Juego::dibujarBannerRound(){
	vector<tuple<string,SDL_Rect , SDL_Rect,SDL_RendererFlip >> dibujables;
	dibujables.push_back(this->roundActual->dibujarBanner());
	return dibujables;
}

vector<tuple<string,SDL_Rect, SDL_Rect ,SDL_RendererFlip >>Juego::dibujar(){

	SDL_RendererFlip flip ;
	vector<tuple<string,SDL_Rect , SDL_Rect,SDL_RendererFlip >> dibujables;
	vector<tuple<Jugador *, int>> zindexs_personajes = obtenerOrdenDibujo();
	vector<int>zindexes = controladorJson->getZindexes(this->roundActual->getNumero());
	this->verificarCambioDeLado();
	int fondos_dibujados = 0;
	int personajes_dibujados = 0;
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
				dibujables.push_back(make_tuple(to_string(zindexes[2])+ to_string(this->roundActual->getNumero()),*origen,*destinoz1,flip));
			}
			else if(fondos_dibujados == 1 ){
				SDL_Rect *origen = parallax->camaraz2();
				SDL_Rect* destinoz2 = parallax->getDestinoZ2();
				dibujables.push_back(make_tuple(to_string(zindexes[1]) + to_string(this->roundActual->getNumero()),*origen,*destinoz2,flip));
			}
			else if(fondos_dibujados == 2 ){
				SDL_Rect *origen = parallax->camaraz3();
				SDL_Rect* destinoz3 = parallax->getDestinoZ3();
				dibujables.push_back(make_tuple(to_string(zindexes[0]) + to_string(this->roundActual->getNumero()),*origen,*destinoz3,flip));
			}
			fondos_dibujados++;
		}
	}
	get<0>(zindexs_personajes[0])->devolverPersonajeActual()->actualizar();
	get<0>(zindexs_personajes[1])->devolverPersonajeActual()->actualizar();
	dibujables.push_back(this->roundActual->getTiempoDibujable());
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
	this->controladorColisiones->setPersonaje1(personaje1);
	this->controladorColisiones->setPersonaje2(personaje2);
	bool finEscenarioDerecha = parallax->finDeEscenarioDerecha();
	bool finEscenarioIzquierda = parallax->finDeEscenarioIzquierda();
	teclado->reiniciar();


	if (evento.window.event == SDL_WINDOWEVENT_RESIZED){//no funciona
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
			 if(! personaje1->colisionaAlaDerecha(personaje2->obtenerRectangulo() )  ){
				if(personaje1->moverDerecha(personaje2,finEscenarioDerecha))
					this->parallax->moverCamaraDerecha();
				controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 a la derecha");
			}
		 }

		 if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_A)){
			if(! personaje1->colisionaAlaIzquierda(personaje2->obtenerRectangulo() )  ){
				if (personaje1->moverIzquierda(personaje2,finEscenarioIzquierda))
					this->parallax->moverCamaraIzquierda();
				controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 a la izquierda");
			}
		 }

		if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_S)){
			personaje1->agacharse();
			controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 agachado");
		}

		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_W)){
			if(!personaje1->estaSaltando()){
				personaje1->saltar();
				controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 1 salta");
			}
		}
		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_J)){
			personaje1->golpe("golpeS");
		}
		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_U)){
			personaje1->golpe("golpeF");
		}

		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_K)){
			personaje1->golpe("patadaS");
		}
		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_I)){
			personaje1->golpe("patadaF");
		}
		if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_L)){
			personaje1->defenderse();
		}
		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_O)){
			personaje1->disparar();
		}
		if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_L)&&teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_K)){
			personaje1->tirar();
		}
		if(teclado->seSoltoUnaTecla(SDL_SCANCODE_S) ||teclado->seSoltoUnaTecla(SDL_SCANCODE_D)|| teclado->seSoltoUnaTecla(SDL_SCANCODE_A)||teclado->seSoltoUnaTecla(SDL_SCANCODE_L)){
				personaje1->cambiarAnimacion("quieto");
		}
		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_E) ){
			this->equipo1->cambiarJugador();
			controladorLogger->registrarEvento("DEBUG", "Juego::Cambio de jugador del equipo 1");
		}

	 }

	 if(puedoMoverPersonaje2 || controladorJson->cantidadClientes() == 1){
		 if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_LEFT)){
			if(! personaje2->colisionaAlaIzquierda(personaje1->obtenerRectangulo()) ){
				if (personaje2->moverIzquierda(personaje1,finEscenarioIzquierda)){
					this->parallax->moverCamaraIzquierda();
				}
			controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 a la izquierda");
			}
		}

		if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_RIGHT)){
		  if(! personaje2->colisionaAlaDerecha(personaje1->obtenerRectangulo()) ){
				if(personaje2->moverDerecha(personaje1, finEscenarioDerecha) )
					this->parallax->moverCamaraDerecha();
				controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 a la derecha");
		   }

		}

		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_UP)){
			if(!personaje2->estaSaltando()){
				personaje2->saltar();
				controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 salta");
			}
		}

		if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_DOWN)){
			personaje2->agacharse();
			controladorLogger->registrarEvento("DEBUG", "Juego::Jugador 2 agachado");
		}
		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_V)){
			personaje2->golpe("golpeS");
		}
		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_B)){
			personaje2->golpe("patadaS");
		}
		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_F)){
			personaje2->golpe("golpeF");
		}
		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_G)){
			personaje2->golpe("patadaF");
		}
		if(teclado->seEstaPresionandoUnaTecla(SDL_SCANCODE_N)){
			personaje2->defenderse();
		}
		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_H)){
			personaje2->disparar();
		}
		if(teclado->seSoltoUnaTecla(SDL_SCANCODE_DOWN) || teclado->seSoltoUnaTecla(SDL_SCANCODE_LEFT) || teclado->seSoltoUnaTecla(SDL_SCANCODE_RIGHT)|| teclado->seSoltoUnaTecla(SDL_SCANCODE_N)){
				personaje2->cambiarAnimacion("quieto");
		}

		if(teclado->sePresionoUnaTecla(SDL_SCANCODE_M)  ){
			this->equipo2->cambiarJugador();
			controladorLogger->registrarEvento("DEBUG", "Juego::Cambio de jugador del equipo 2");
		}

	 }

	 this->controladorColisiones->resolverColisiones();

}

std::vector<std::string> Juego::gameMenu(){
	std::vector<std::string> nombres_jugadores;
	nombres_jugadores.push_back("Venom");
	nombres_jugadores.push_back("Spiderman");
	nombres_jugadores.push_back("Venom");
	nombres_jugadores.push_back("Hulk");
	return nombres_jugadores;
}

Equipo * Juego::getGanadorUltimoRound(){
	return this->equipo1;
}

void Juego::reiniciarPersonajes(){
	//por ahora solo vuelven a la pocicion inicial
	//TODO reiniciar vida y otras cossas
	this->jugadorActualEquipo1->devolverPersonajeActual()->cambio();
	this->jugadorActualEquipo2->devolverPersonajeActual()->cambio();
}

void Juego::obtenerVidas(int *vidas){
	Personaje *personaje1 = this->equipo1->obtenerJugador1()->devolverPersonajeActual();
	Personaje *personaje2 = this->equipo1->obtenerJugador2()->devolverPersonajeActual();
	Personaje *personaje3 = this->equipo2->obtenerJugador1()->devolverPersonajeActual();
	Personaje *personaje4 = this->equipo2->obtenerJugador2()->devolverPersonajeActual();

	string nombre = "";
	for (int i = 0; i < 4; i++){
		if (i == 0) nombre = "CapitanAmerica";
		else if (i == 1) nombre = "MegaMan";
		else if (i == 2) nombre = "Spiderman";
		else nombre = "Venom";

		if(personaje1->getNombre() == nombre) vidas[i] = personaje1->obtenerVida();
		else if(personaje2->getNombre() == nombre) vidas[i] = personaje2->obtenerVida();
		else if(personaje3->getNombre() == nombre) vidas[i] = personaje3->obtenerVida();
		else vidas[i] = personaje4->obtenerVida();
	}


}
