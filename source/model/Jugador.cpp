#include <Jugador.hpp>
#include <Personaje.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>

Jugador::Jugador(ControladorGrafico &graficos, std::string nombrePersonaje1, std::string nombrePersonaje2, int posicionXinicial, SDL_RendererFlip flip, bool ladoDerecho){
	this->personaje1 = new Personaje(graficos,nombrePersonaje1, posicionXinicial, flip);
	this->personaje2 = new Personaje(graficos,nombrePersonaje2, posicionXinicial, flip);
	this->personajeActual = this->personaje1;
	this->personajePrincipal = true;
	this->ladoDerecho = ladoDerecho;
}

void Jugador::cambiarPersonaje(){
	if (this->personajePrincipal){
		this->personajeActual = this->personaje2;
		this->personajePrincipal = false;
		this->personaje2->Cambio();
	}
	else{
		this->personajeActual->detenerAnimacion();
		this->personajeActual = this->personaje1;
		this->personajePrincipal = true;
		this->personaje1->Cambio();
	}

}

void Jugador::personajeActualDibujar(ControladorGrafico &graficos){
	this->personajeActual->dibujar(graficos);
}

Personaje* Jugador::devolverPersonajeActual(){
	return this->personajeActual;
}


float Jugador::posicionActual(){
	return this->personajeActual->getPosX();
}

void Jugador::Flip(){
	this->personajeActual->Flip();
}

bool Jugador::estaDelladoDerecho(){
	return this->ladoDerecho;
}

void Jugador::cambiarDeLado(){
	this->ladoDerecho = not this->ladoDerecho;
	this->personajeActual->Flip();
}
