#include <Jugador.hpp>
#include <Personaje.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>

Jugador::Jugador(std::string nombrePersonaje, int posicionXinicial, SDL_RendererFlip flip, bool ladoDerecho, int idCliente){
	this->personaje = new Personaje(nombrePersonaje, posicionXinicial, flip);
	this->ladoDerecho = ladoDerecho;
	this->nombre = nombrePersonaje;
	this->id = idCliente;
}

Jugador::~Jugador(){
	delete personaje;
}

void Jugador::cambiarPersonaje(){
	this->personaje->cambio();

}

Personaje* Jugador::devolverPersonajeActual(){
	return this->personaje;
}

std::string Jugador::nombreJugador(){
	return this->nombre;
}


float Jugador::posicionActual(){
	return this->personaje->getPosX();
}

bool Jugador::estaDelladoDerecho(){
	return this->ladoDerecho;
}

void Jugador::cambiarDeLado(){
	this->ladoDerecho = not this->ladoDerecho;
	this->personaje->Flip();
}

void Jugador::actualizarPiso(){
	this->personaje->actualizarPiso();
}

int Jugador::obtenerId(){
	return(this->id);
}
