#include <Jugador.hpp>
#include <Personaje.hpp>
#include <ConfiguracionGlobal.hpp>
#include <Sprite.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>

Jugador::Jugador(ControladorGrafico &graficos, std::string nombrePersonaje1, std::string nombrePersonaje2){
	this->personaje1 = new Personaje(graficos,nombrePersonaje1);
	this->personaje2 = new Personaje(graficos,nombrePersonaje2);
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
void Jugador::personajeActualMoverDerecha(){
	this->personaje1->MoverDerecha();
	this->personaje2->MoverDerecha();
}
void Jugador::personajeActualMoverIzquierda(){
	this->personaje1->MoverIzquierda();
	this->personaje2->MoverIzquierda();
}

void Jugador::personajeActualSaltar(){
	this->personaje1->Saltar();
	this->personaje2->Saltar();
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


