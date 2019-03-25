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
		void beginNewFrame();
		//Se llama cada vez que se suelta una tecla
		void keyUpEvent(const SDL_Event& evento);
		//SE llama cada vez que se presiona una tecla
		void keyDownEvent(const SDL_Event& evento);
		//Es true si se presiono la "tecla" que recibe como parametre en el frame actual
		bool wasKeyPressed(SDL_Scancode tecla);
		//Es true si se suelta (deja de apretar) la "tecla" que recibe como parametre en el frame actual
		bool wasKeyReleased(SDL_Scancode tecla);
		//Es true si se esta presionando la "tecla" que recibe como parametre en el frame actual
		bool isKeyHeld(SDL_Scancode tecla);


	private:
		std::map<SDL_Scancode, bool> _heldKeys;
		std::map<SDL_Scancode, bool> _pressedKeys;
		std::map<SDL_Scancode, bool> _releasedKeys;
};




#endif /* HEADERS_CONTROLER_CONTROLADORTECLADO_HPP_ */
