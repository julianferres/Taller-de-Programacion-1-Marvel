#ifndef JUGADOR_HPP_
#define JUGADOR_HPP_

#include <string>
#include <SDL2/SDL_image.h>

class Personaje;
class ControladorGrafico;

class Jugador{

	public:

		Jugador(ControladorGrafico &grafico, std::string nombrePersonaje1,
				std::string nombrePersonaje2, int posicionXinicial, SDL_RendererFlip flip, bool ladoDerecho);
		~Jugador();
		void personajeActualDibujar(ControladorGrafico &grafico);
		void cambiarPersonaje();
		void Flip();
		Personaje * devolverPersonajeActual();
		float posicionActual();
		bool estaDelladoDerecho();
		void cambiarDeLado();
	private:

		Personaje *personaje1;
		Personaje *personaje2;
		Personaje *personajeActual;
		bool personajePrincipal;
		bool ladoDerecho;
};

#endif
