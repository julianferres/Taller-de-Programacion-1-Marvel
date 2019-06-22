#include <Personaje.hpp>
#include <ControladorJson.hpp>
#include <string>
#include <math.h>
#include <ControladorLogger.hpp>
#include <iostream>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

#define constanteDeAltura 7500 //sale de querer saltar 375 unidades
#define constanteTiempoCiclos 0.3

using namespace std;

Personaje::~Personaje(){
	delete spriteAnimado;
}

Personaje::Personaje(string nombre, int posicionXinicial, SDL_RendererFlip flip){
	this->vida = 100;
	this->habilitado = true;
	if(nombre == "SinSprite"){
		this->zindex = 99;
		this->spriteAnimado=new SpriteAnimado(nombre);
		constanteEstiramientoHorizontal=1;
		constanteEstiramientoVertical=1;
		this->alto = controladorJson->alturaPersonajeDefault();
		this->ancho = controladorJson->anchoPersonajeDefault();
		controladorLogger->registrarEvento("ERROR", "El personaje elegido es inexistente, se carga una imagen por defecto");
	}
	else {
		this->zindex = controladorJson->zindexPersonaje(nombre);
		this->spriteAnimado=new SpriteAnimado(nombre);
		constanteEstiramientoHorizontal=controladorJson->anchoPersonaje(nombre)/spriteAnimado->getAncho();
		constanteEstiramientoVertical=controladorJson->alturaPersonaje(nombre)/spriteAnimado->getAlto();
		this->alto =constanteEstiramientoVertical*spriteAnimado->getAlto();
		this->ancho = constanteEstiramientoHorizontal*spriteAnimado->getAncho();
	}

	this->posicionYdefault= controladorJson->alturaVentana() - controladorJson->getAlturaPiso();
	this->nombre = nombre;
	this->posy = posicionYdefault - 2*spriteAnimado->getAlto();
	this->velocidadInicial = sqrt(constanteDeAltura);
	this->posx= posicionXinicial;
	this->posicionXinicial = posicionXinicial;
	this->flip = flip;
	anchoDefault=spriteAnimado->getAncho();
	controladorLogger->registrarEvento("INFO", "Personaje:: Personaje creado: "+nombre);
	if(nombre == "SinSprite")
		cout << this->alto << " - " << this->ancho << endl;
}

void Personaje::actualizar(Personaje *enemigo){
	if(saltando) this->saltar(enemigo);
	this->spriteAnimado->update();
	if(this->nombre != "SinSprite"){
		this->alto =constanteEstiramientoVertical*spriteAnimado->getAlto();
		this->ancho = constanteEstiramientoHorizontal*spriteAnimado->getAncho();
	}
	if(!saltando) posy = posicionYdefault-alto;

}

void Personaje::cambiarAnimacion(string nombre){
	if (agachado)
		agachado=false;
	if(defendiendo)
		defendiendo = false;
	this->spriteAnimado->cambiarAnimacion(nombre);
}

bool Personaje::moverDerecha(Personaje *enemigo,bool finEscenarioDerecha){
	SDL_Rect rect_enemigo = enemigo->obtenerRectangulo();
	if(!saltando){
		if(flip==0)
			this->spriteAnimado->iniciarAnimacion("movDerecha");
		else
			this->spriteAnimado->iniciarAnimacion("movIzquierda");
	}

	if(posx + ancho > (controladorJson-> getLimiteFondoDer())){
		if (rect_enemigo.x > (controladorJson->getLimiteFondoIzq()) && !finEscenarioDerecha){
			enemigo->correrAIzquierda();
			controladorLogger->registrarEvento("DEBUG", "Personaje::Personaje en el limite derecho. Se corre el oponente a la izquierda");
			return true;
		}
		controladorLogger->registrarEvento("DEBUG", "Personaje::Ambos jugadores en el borde de la pantalla.");
		return false;
	}
	this->posx=this->posx+velocidad;
	controladorLogger->registrarEvento("DEBUG", "Personaje::Personaje se mueve a la derecha");
	return false;
}

bool Personaje::moverIzquierda(Personaje *enemigo,bool finEscenarioIzquierda){
	SDL_Rect rect_enemigo = enemigo->obtenerRectangulo();
	if(!saltando){
			if(flip==0)
				this->spriteAnimado->iniciarAnimacion("movIzquierda");
			else
				this->spriteAnimado->iniciarAnimacion("movDerecha");
	}

	if(posx  < controladorJson->getLimiteFondoIzq()){
		if (rect_enemigo.x + rect_enemigo.w < controladorJson->getLimiteFondoDer() && !finEscenarioIzquierda){
			enemigo->correrADerecha();
			controladorLogger->registrarEvento("DEBUG", "Personaje:: Personaje en el limite izquierdo. Se corre el oponente a la derecha");
			return true;
		}
		controladorLogger->registrarEvento("DEBUG", "Personaje::Ambos jugadores en el borde de la pantalla.");
		return false;
	}

	this->posx=this->posx-velocidad;

	controladorLogger->registrarEvento("DEBUG", "Personaje::Personaje se mueve a la izquierda");
	return false;
}

void Personaje::correrAIzquierda(){
	if(posx  < controladorJson->getLimiteFondoIzq())
			return;
	this->posx=this->posx-velocidad;
}

void Personaje::correrADerecha(){
	if(posx + ancho > controladorJson->getLimiteFondoDer())
			return;
	this->posx=this->posx+velocidad;
}
void Personaje::golpe(string tipoDeGolpe){
	if(saltando){
		if(tipoDeGolpe=="golpeS" || tipoDeGolpe=="golpeF")
			this->spriteAnimado->iniciarAnimacion("golpeSaltando");
		if(tipoDeGolpe=="patadaS" || tipoDeGolpe=="patadaF")
			this->spriteAnimado->iniciarAnimacion("patadaSaltando");
	}

	else{
		if(agachado){
			if(tipoDeGolpe=="golpeS" || tipoDeGolpe=="golpeF")
				this->spriteAnimado->iniciarAnimacion("golpeA");
			if(tipoDeGolpe=="patadaS" || tipoDeGolpe=="patadaF")
				this->spriteAnimado->iniciarAnimacion("patadaA");
		}
		else
			this->spriteAnimado->iniciarAnimacion(tipoDeGolpe);

	}
}

void Personaje::agacharse(){
	if(saltando ) return;
	if(!agachado){
		agachado = true;
		this->spriteAnimado->iniciarAnimacion("agacharse");
	}
}
void Personaje::disparar(){
	if(saltando|| agachado) return;
	this->spriteAnimado->iniciarAnimacion("disparar");
}
void Personaje::defenderse(){
	if(saltando) return;
	if(!defendiendo){
		defendiendo = true;
		this->spriteAnimado->iniciarAnimacion("defensa");
	}
}
void Personaje::tirar(){
	if(saltando|| agachado) return;
	this->spriteAnimado->iniciarAnimacion("tirar");
}
void Personaje::recibirGolpe(){
	this->spriteAnimado->iniciarAnimacion("recibirGolpe");
}

void Personaje::cambio(){
	if(posicionXinicial < controladorJson->anchoVentana()/2)
		this->posx = 0;
	else
		this->posx = controladorJson->anchoVentana()- 2*spriteAnimado->getAncho();

	this->spriteAnimado->iniciarAnimacion("cambioEntrada");
}

void Personaje::saltar(Personaje *enemigo){
	SDL_Rect rectanguloFuturo = { static_cast<int>(posx), static_cast<int>(posy), ancho,alto*alto};
	SDL_Rect rect_enemigo=enemigo->obtenerRectangulo();
	SDL_Rect rect_mio=obtenerRectangulo();
	bool saltarPermitido = true;

	if(!moviendoDer && !moviendoIzq){
		if(enemigo->posx<posx){moviendoIzq=true;}
		else if (enemigo->posx>posx){moviendoDer=true;}
	}
if(SDL_HasIntersection(&rectanguloFuturo, &rect_enemigo) && posy + alto < enemigo->posy){

		posy-=velocidad/5;
		if (moviendoIzq){
			posx-=30;
			enemigo->correrADerecha();

		}
		if (moviendoDer && posx<controladorJson->anchoVentana()){
			posx+=30;
			enemigo->correrAIzquierda();

		}
		this->spriteAnimado->cambiarAnimacion("salto");
		return;
	}


	if(!saltando){
		saltarPermitido = this->spriteAnimado->iniciarAnimacion("salto");
		if(saltarPermitido) saltando = true;
		else saltando = false;
	}
	else{

		if(alturaActualSalto <= 0 && tiempo != 0 ){
			saltando = false;
			moviendoIzq=false;
			moviendoDer=false;
			tiempo = 0;
			posy=posicionYdefault - 2*spriteAnimado->getAlto();
		}
		else{
			tiempo += constanteTiempoCiclos;
			float alturaPrevia  = alturaActualSalto;
			alturaActualSalto = (velocidadInicial - 4.9* tiempo)*tiempo;
			posy -= (alturaActualSalto - alturaPrevia);
		}
	}
}

bool Personaje::estaSaltando(){
	return saltando;
}

void Personaje::Flip(){
	if (this->flip == 0)
		this->flip = SDL_FLIP_HORIZONTAL;
	else
		this->flip = SDL_FLIP_NONE;

}

SDL_RendererFlip Personaje::getFlip(){
	return this->flip;
}

float Personaje::getPosX(){
	return this->posx;
}

float Personaje::getPosY(){
	return this->posy;
}

void Personaje::forzarPosicion(float x, float y){
	this->posx = x;
	this->posy = y;
}

SDL_Rect  Personaje::obtenerRectangulo(){
	int posicionXdibujable = posx;
	if(flip)
		posicionXdibujable = posx+ constanteEstiramientoHorizontal*(-spriteAnimado->getAncho()+anchoDefault);
	SDL_Rect rectangulo = { static_cast<int>(posicionXdibujable), static_cast<int>(posy), ancho, alto};
	return rectangulo;
}

int Personaje::zindexPersonaje(){
	return zindex;
}

std::string Personaje::getNombre(){
	return nombre;
}

void Personaje::actualizarPiso(){
	this->posy = controladorJson->alturaVentana() - controladorJson->getAlturaPiso() - alto;
}

SpriteAnimado *Personaje::obtenerSprite(){
	return this->spriteAnimado;
}


bool Personaje::colisionaAlaDerecha(SDL_Rect rectanguloOponente){
	SDL_Rect rectanguloFuturo = { static_cast<int>(posx)+velocidad, static_cast<int>(posy), ancho, alto};
	return SDL_HasIntersection( &rectanguloFuturo, &rectanguloOponente );
}

bool Personaje::colisionaAlaIzquierda(SDL_Rect rectanguloOponente){
	SDL_Rect rectanguloFuturo = { static_cast<int>(posx)-velocidad, static_cast<int>(posy), ancho, alto};
	return SDL_HasIntersection( &rectanguloFuturo, &rectanguloOponente );
}

void Personaje::restarVida(int cantidad){
	this->vida -= cantidad;
}

int Personaje::obtenerVida(){
	return this->vida;
}

void Personaje::reiniciarVida(){
	this->vida = 100;
}

string Personaje::getSonido(){
	return spriteAnimado->getSonido();
}

void Personaje::bloquear(){
	this->habilitado = false;
}

bool Personaje::bloqueado(){
	return !this->habilitado;
}

void Personaje::habilitar(){
	this->habilitado = true;
}

