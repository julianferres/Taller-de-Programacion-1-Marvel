/*
 * ContrroladorTeclado.hpp
 *
 *  Created on: Mar 24, 2019
 *      Author: luupesado
 */

#ifndef HEADERS_CONTROLER_CONTROLADORTECLADO_HPP_
#define HEADERS_CONTROLER_CONTROLADORTECLADO_HPP_

#include<SDL2/SDL.h>
#include <map>

class ControladorTeclado{
	public:
		void empezarNuevoFrame();
		//Se llama cada vez que se suelta una tecla
		void eventoSoltarTecla(const SDL_Event& evento);
		//SE llama cada vez que se presiona una tecla
		void eventoPresionarTecla(const SDL_Event& evento);
		//Es true si se presiono la "tecla" que recibe como parametre en el frame actual
		bool sePresionoUnaTecla(SDL_Scancode tecla);
		//Es true si se suelta (deja de apretar) la "tecla" que recibe como parametre en el frame actual
		bool seSoltoUnaTecla(SDL_Scancode tecla);
		//Es true si se esta presionando la "tecla" que recibe como parametre en el frame actual
		bool seEstaPresionandoUnaTecla(SDL_Scancode tecla);


	private:
		std::map<SDL_Scancode, bool> _teclasSostenidas;
		std::map<SDL_Scancode, bool> _teclasPresionadas;
		std::map<SDL_Scancode, bool> _teclasSoltadas;
};




#endif /* HEADERS_CONTROLER_CONTROLADORTECLADO_HPP_ */
