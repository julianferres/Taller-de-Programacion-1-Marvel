#ifndef HEADERS_CONTROLER_CONTROLADORSONIDO_HPP_
#define HEADERS_CONTROLER_CONTROLADORSONIDO_HPP_

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <map>
#include <tuple>

using namespace std;

class ControladorSonido{


public:
	ControladorSonido();
	~ControladorSonido();
	void correrSonido(const char* nombre,bool esperar);
	void correrCancionFondo(const char* nombre,int repeticiones);
	void detenerCancion();
	void finalizarCancion();
	void cargarGolpes(string personaje);
	void correrSonidoAnimacion(string personaje,string golpe);

private:
	map<tuple<string,string>,string>sonidos;

};


#endif
