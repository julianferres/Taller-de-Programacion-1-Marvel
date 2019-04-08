#include <Jugador.hpp>
#include <Personaje.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>

Jugador::Jugador(ControladorGrafico &graficos, std::string nombrePersonaje1, std::string nombrePersonaje2, int posicionXinicial, SDL_RendererFlip flip){
	this->personaje1 = new Personaje(graficos,nombrePersonaje1, posicionXinicial, flip);
	this->personaje2 = new Personaje(graficos,nombrePersonaje2, posicionXinicial, flip);
	this->personajeActual = this->personaje1;
	this->personajePrincipal = true;
}

void Jugador::cambiarPersonaje(){
	if (this->personajePrincipal){
		this->personajeActual = this->personaje2;
		this->personajePrincipal = false;
	}else{
		this->personajeActual = this->personaje1;
		this->personajePrincipal = true;
	}
}

void Jugador::personajeActualDibujar(ControladorGrafico &graficos){
	this->personajeActual->dibujar(graficos);
}

float Jugador::obtenerPosicionXPersonaje(bool posicionDer){
	if (posicionDer){
		return ((this->personajeActual)->getXDer());
	}
	return ((this->personajeActual)->getX());
}

Personaje* Jugador::devolverPersonajeActual(){
	return this->personajeActual;
}

