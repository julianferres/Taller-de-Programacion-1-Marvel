#include <Personaje.hpp>
#include <ControladorJson.hpp>
#include <string>
#include <math.h>
#include <ControladorLogger.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

#define constanteDeAltura 20.2f //Viene de despejar la velocidad en funcion a una h_max = 2*alto
#define constanteTiempoCiclos 0.3

using namespace std;

Personaje::~Personaje(){
	delete spriteAnimado;
}

Personaje::Personaje(string nombre, int posicionXinicial, SDL_RendererFlip flip){
	std::string path = controladorJson->pathImagen(nombre);
	if(nombre == "sinSprite"){
		path = "contents/images/sinSprite.png";
		this->alto = controladorJson->alturaPersonajeDefault();
		this->ancho =controladorJson->anchoPersonajeDefault();
		this->spriteAnimado=new SpriteAnimado(nombre);
		this->zindex = 99;
		controladorLogger->registrarEvento("ERROR", "El personaje elegido es inexistente, se carga una imagen por defecto");
	}
	else{
		this->alto = controladorJson->alturaPersonaje(nombre);
		this->ancho = controladorJson->anchoPersonaje(nombre);
		this->spriteAnimado=new SpriteAnimado(nombre);
		this->zindex = controladorJson->zindexPersonaje(nombre);
	}
	this->nombre = nombre;
	this->posy = controladorJson->alturaVentana() - controladorJson->getAlturaPiso() - alto;
	this->velocidadInicial = sqrt(constanteDeAltura * alto);
	this->posx= posicionXinicial;
	this->posicionXinicial = posicionXinicial;
	this->flip = flip;
	controladorLogger->registrarEvento("INFO", "Personaje:: Personaje creado: "+nombre);

}

void Personaje::actualizar(){
	if(saltando)
		this->saltar();
	this->spriteAnimado->update();
}

void Personaje::cambiarAnimacion(string nombre){
	if (agachado){
		agachado=false;
	}
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
		if(tipoDeGolpe=="golpeS"){
			this->spriteAnimado->iniciarAnimacion("golpeSS");
		}
		if(tipoDeGolpe=="golpeF"){
			this->spriteAnimado->iniciarAnimacion("golpeSF");
		}
		if(tipoDeGolpe=="patadaS"){
			this->spriteAnimado->iniciarAnimacion("patadaSS");
		}
		if(tipoDeGolpe=="patadaF"){
			this->spriteAnimado->iniciarAnimacion("patadaSF");
		}

	}
	else{
		if(agachado){
			if(tipoDeGolpe=="golpeS"){
				this->spriteAnimado->iniciarAnimacion("golpeAS");
			}
			if(tipoDeGolpe=="golpeF"){
				this->spriteAnimado->iniciarAnimacion("golpeAF");
			}
			if(tipoDeGolpe=="patadaS"){
				this->spriteAnimado->iniciarAnimacion("patadaAS");
			}
			if(tipoDeGolpe=="patadaF"){
				this->spriteAnimado->iniciarAnimacion("patadaAF");
			}
		}
		else{
			this->spriteAnimado->iniciarAnimacion(tipoDeGolpe);
		}
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
	if(saltando|| agachado) return;
	this->spriteAnimado->iniciarAnimacion("defensa");
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
		this->posx = controladorJson->anchoVentana()-ancho;

	this->spriteAnimado->iniciarAnimacion("cambioEntrada");
}

void Personaje::saltar(){
	bool saltarPermitido = true;
	if( ! saltando){
		saltarPermitido = this->spriteAnimado->iniciarAnimacion("salto");
		if(saltarPermitido) saltando = true;
		else saltando = false;
	}
	else{
		if(alturaActualSalto <= 0 && tiempo != 0 ){
			saltando = false;
			tiempo = 0;
			posy=controladorJson->alturaVentana() - controladorJson->getAlturaPiso() - alto;
		}
		else{
			tiempo += constanteTiempoCiclos;
			float alturaPrevia  = alturaActualSalto;
			alturaActualSalto = (velocidadInicial - 4.9* tiempo)*tiempo;
			posy -= (alturaActualSalto - alturaPrevia);
		}
	}
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

SDL_Rect  Personaje::obtenerRectangulo(){
	SDL_Rect rectangulo = { static_cast<int>(posx), static_cast<int>(posy), ancho, alto};
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

/*
bool Personaje::colisionaAlaDerecha(SDL_Rect rectanguloOponente){
	SDL_Rect rectanguloFuturo = { static_cast<int>(posx)+15, static_cast<int>(posy), ancho, alto};
	return SDL_HasIntersection( &rectanguloFuturo, &rectanguloOponente );
}

bool Personaje::colisionaAlaIzquierda(SDL_Rect rectanguloOponente){
	SDL_Rect rectanguloFuturo = { static_cast<int>(posx)-15, static_cast<int>(posy), ancho, alto};
	return SDL_HasIntersection( &rectanguloFuturo, &rectanguloOponente );
}*/


