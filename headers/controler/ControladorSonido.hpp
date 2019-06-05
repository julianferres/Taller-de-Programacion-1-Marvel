#ifndef HEADERS_CONTROLER_CONTROLADORSONIDO_HPP_
#define HEADERS_CONTROLER_CONTROLADORSONIDO_HPP_

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>

class ControladorSonido{


public:
	ControladorSonido();
	~ControladorSonido();
	void correrSonido(const char* nombre);
	void correrCancionFondo(const char* nombre,int repeticiones);
	void detenerCancion();
	void finalizarCancion();

};


#endif
