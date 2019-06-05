#ifndef HEADERS_CONTROLER_CONTROLADORSONIDO_HPP_
#define HEADERS_CONTROLER_CONTROLADORSONIDO_HPP_

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>

class ControladorSonido{


public:
	ControladorSonido();
	~ControladorSonido();
	void correrCancion(const char* nombre,int repeticiones);
	void detenerCancion();

};


#endif
