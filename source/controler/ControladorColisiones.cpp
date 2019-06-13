#include <ControladorColisiones.hpp>
#include <iostream>

using namespace std;

ControladorColisiones::ControladorColisiones(){
	animacion["disparar"]=1;
	animacion["golpeS"]=1;
	animacion["golpeF"]=1;
	animacion["golpeSaltando"]=1;
	animacion["golpeA"]=1;
	animacion["patadaS"]=1;
	animacion["patadaF"]=1;
	animacion["patadaSaltando"]=1;
	animacion["patadaA"]=1;
	animacion["movDerecha"]=0;
	animacion["movIzquierda"]=0;
	animacion["salto"]=0;
	animacion["agacharse"]=0;

}

void ControladorColisiones::setPersonaje1(Personaje * personaje){
	this->personajeEquipo1 = personaje;
	this->recPersonaje1=personaje->obtenerRectangulo();
}

void ControladorColisiones::setPersonaje2(Personaje * personaje){
	this->personajeEquipo2 = personaje;
	this->recPersonaje2=personaje->obtenerRectangulo();
}

bool ControladorColisiones::hayColision(){
	return SDL_HasIntersection( &recPersonaje1, &recPersonaje2 );
}


void ControladorColisiones::resolverColisiones(){
	if(hayColision()){
		string animacionPersonaje1 = personajeEquipo1->obtenerSprite()->getAnimacionActual();
		string animacionPersonaje2 = personajeEquipo2->obtenerSprite()->getAnimacionActual();
		if(animacion[animacionPersonaje1]==1){//personaje1 esta golpeando
			//personajeEquipo2->cambiarAnimacion("recibirGolpe");
			puts("golpea el jugador 1");
		}

		if(animacion[animacionPersonaje2]==1){//personaje2 esta golpeando
			//personajeEquipo1->cambiarAnimacion("recibirGolpe");
			puts("golpea el jugador 2");
		}



















	}
}
