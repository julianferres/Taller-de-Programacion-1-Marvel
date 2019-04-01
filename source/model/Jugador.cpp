#include <Jugador.hpp>
#include <Personaje.hpp>
#include <ConfiguracionGlobal.hpp>
#include <Sprite.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>

Jugador::Jugador(){

}

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
	this->personajeActual->MoverDerecha();
}
void Jugador::personajeActualMoverIzquierda(){
	this->personajeActual->MoverIzquierda();
}

void Jugador::personajeActualDibujar(ControladorGrafico &graficos){
	this->personajeActual->dibujar(graficos);
}
