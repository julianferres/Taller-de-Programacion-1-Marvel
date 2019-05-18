#ifndef JUGADOR_HPP_
#define JUGADOR_HPP_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Personaje;
class ControladorGrafico;

class Jugador{

	public:

		Jugador(std::string nombrePersonaje, int IDcliente,SDL_RendererFlip flip, bool ladoDerecho, int idCliente);
		~Jugador();
		void cambiarPersonaje();
		void cambiarDeLado();
		void actualizarPiso();
		float posicionActual();
		bool estaDelladoDerecho();
		SDL_RendererFlip getFlip();
		std::string nombreJugador();
		Personaje * devolverPersonajeActual();
		int obtenerId();
	private:

		Personaje *personaje;
		bool ladoDerecho;
		std::string nombre;
		int tipoTeclado;
		int id;

};

#endif
