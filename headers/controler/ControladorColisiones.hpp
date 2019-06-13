#ifndef HEADERS_CONTROLER_CONTROLADORCOLISIONES_HPP_
#define HEADERS_CONTROLER_CONTROLADORCOLISIONES_HPP_

#include <Personaje.hpp>
#include <map>

using namespace std;

class Personaje;

class ControladorColisiones{

public:

	ControladorColisiones();
	bool hayColision();
	void setPersonaje1(Personaje* personaje);
	void setPersonaje2(Personaje* personaje);
	void resolverColisiones();

private:
	Personaje* personajeEquipo1;
	Personaje* personajeEquipo2;
	SDL_Rect recPersonaje1;
	SDL_Rect recPersonaje2;
	map<string,int> animacion; //0 si es movimiento,1 si es golpe
};



#endif
