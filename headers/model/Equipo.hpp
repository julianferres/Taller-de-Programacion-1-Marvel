#ifndef EQUIPO_HPP_
#define EQUIPO_HPP_

#include <Jugador.hpp>
#include <Personaje.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>

class Jugador;

class Equipo{

public:
	Equipo(Jugador *jugador1, Jugador *jugador2);
	void cambiarJugador();
	Jugador *JugadorActual();
	void cambiarDeLado();
	void actualizarPiso();
	int obtenerIdJugadorActual();
	int obtenerIdCompaniero();
	void actualizarConexion(int idCliente);
	bool TecladoHabilitado();
	void habilitarTeclado();
private:
	bool tecladoHabilitado = false;
	vector<Jugador*> jugadores;
	Jugador * jugadorActual ;

};



#endif
