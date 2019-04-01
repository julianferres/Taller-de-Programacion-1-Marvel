#ifndef HEADERS_MODEL_JUGADOR_HPP_
#define HEADERS_MODEL_JUGADOR_HPP_

#include <string>
class Personaje;
class ControladorGrafico;
class Jugador{
public:
	Jugador();
	Jugador(ControladorGrafico &grafico, std::string nombrePersonaje1,
			std::string nombrePersonaje2);
	~Jugador();
	void personajeActualMoverDerecha();
	void personajeActualMoverIzquierda();
	void personajeActualDibujar(ControladorGrafico &grafico);
	void cambiarPersonaje();
private:

	Personaje *personaje1;
	Personaje *personaje2;
	Personaje *personajeActual;
	bool personajePrincipal;
//	Personaje * devolverPersonajeActual();


};


#endif /* HEADERS_MODEL_JUGADOR_HPP_ */
