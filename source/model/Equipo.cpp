#include <Equipo.hpp>
#include <Jugador.hpp>
#include <Personaje.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>
#include <vector>

Equipo::Equipo(Jugador *jugador1, Jugador *jugador2){
	jugadores.push_back(jugador1);
	jugadores.push_back(jugador2);
	jugadorActual = jugadores[0];
}

void Equipo::cambiarJugador(){
	if(jugadorActual==jugadores[0]){
		jugadorActual= jugadores[1];
	}
	else{
		jugadorActual = jugadores[0];
	}
	jugadorActual->cambiarPersonaje();
}

Jugador *Equipo::JugadorActual(){
	return this->jugadorActual;
}

void Equipo::cambiarDeLado(){
	jugadores[0]->cambiarDeLado();
	jugadores[1]->cambiarDeLado();
}

void Equipo::actualizarPiso(){
	jugadores[0]->actualizarPiso();
	jugadores[1]->actualizarPiso();
}

int Equipo::obtenerIdJugadorActual(){
	return(this->jugadorActual->obtenerId());
}

void Equipo::actualizarConexion(int idCliente){
	if(idCliente == this->jugadores[0]->obtenerId() || idCliente == this->jugadores[1]->obtenerId())
		this->tecladoHabilitado = !this->tecladoHabilitado;
}

bool Equipo::TecladoHabilitado(){
	return this->tecladoHabilitado;
}
