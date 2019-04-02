#ifndef JUGADOR_HPP_
#define JUGADOR_HPP_

#include <string>

class Personaje;
class ControladorGrafico;

class Jugador{

	public:

		Jugador(ControladorGrafico &grafico, std::string nombrePersonaje1,
				std::string nombrePersonaje2);
		~Jugador();
		void personajeActualMoverDerecha();
		void personajeActualMoverIzquierda();
		void personajeActualSaltar();
		void personajeActualDibujar(ControladorGrafico &grafico);
		void cambiarPersonaje();
		float obtenerPosicionXPersonaje(bool posicionDer);

	private:

		Personaje *personaje1;
		Personaje *personaje2;
		Personaje *personajeActual;
		bool personajePrincipal;

	//	Personaje * devolverPersonajeActual();

};

#endif
