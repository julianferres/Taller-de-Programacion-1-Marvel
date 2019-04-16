#ifndef HEADERS_CONTROLER_CONTROLADORTECLADO_HPP_
#define HEADERS_CONTROLER_CONTROLADORTECLADO_HPP_

#include<map>
#include <SDL2/SDL.h>

class ControladorTeclado{

	public:

		void reiniciar();
		void eventoPresionarTecla(const SDL_Event& evento);
		void eventoSoltarTecla(const SDL_Event& evento);
		bool sePresionoUnaTecla(SDL_Scancode tecla);
		bool seSoltoUnaTecla(SDL_Scancode tecla);
		bool seEstaPresionandoUnaTecla(SDL_Scancode tecla);


	private:
		std::map<SDL_Scancode, bool> _heldKeys;
		std::map<SDL_Scancode, bool> _pressedKeys;
		std::map<SDL_Scancode, bool> _releasedKeys;
};


#endif
