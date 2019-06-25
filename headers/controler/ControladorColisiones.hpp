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
	void resolverColisiones(bool tiempoCorriendo);
	void resolverDisparos(Personaje* personaje1,Personaje* personaje2,bool tiempoCorriendo);
	void moverRectangulo(string animacionPersonaje1, string animacionPersonaje2);

private:
	Personaje* personajeEquipo1;
	Personaje* personajeEquipo2;
	SDL_Rect recPersonaje1;
	SDL_Rect recPersonaje2;
	map<string,int> golpesSuaves;
	map<string,int> golpesFuertes;
	map<string,int> movimientos;
	map<string,int> movimientosEspeciales;
	map<string,int>offset;
	bool disparoAcertado1=false;
	bool disparoAcertado2=false;

};



#endif
