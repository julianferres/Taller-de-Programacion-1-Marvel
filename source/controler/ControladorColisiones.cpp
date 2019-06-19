#include <ControladorColisiones.hpp>
#include <iostream>

using namespace std;

ControladorColisiones::ControladorColisiones(){
	golpesFuertes["disparar"]=1;
	golpesSuaves["golpeS"]=1;
	golpesFuertes["golpeF"]=1;
	golpesSuaves["golpeSaltando"]=1;
	golpesSuaves["golpeA"]=1;
	golpesSuaves["patadaS"]=1;
	golpesFuertes["patadaF"]=1;
	golpesFuertes["patadaSaltando"]=1;
	golpesSuaves["patadaA"]=1;
	movimientos["movDerecha"]=1;
	movimientos["movIzquierda"]=1;
	movimientos["salto"]=1;
	movimientos["agacharse"]=1;
	movimientosEspeciales["tirar"]=1;

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


void ControladorColisiones::resolverColisiones(bool tiempoCorriendo){
	if(hayColision()){
		string animacionPersonaje1 = personajeEquipo1->obtenerSprite()->getAnimacionActual();
		string animacionPersonaje2 = personajeEquipo2->obtenerSprite()->getAnimacionActual();
		if(golpesSuaves[animacionPersonaje1]&& animacionPersonaje2!="recibirGolpe" ){//personaje1 esta golpeando
			if(animacionPersonaje2=="defensa"){
				if(tiempoCorriendo)
					personajeEquipo2->restarVida(1);
			}
			else{
				personajeEquipo2->cambiarAnimacion("recibirGolpe");
				if (tiempoCorriendo)
					personajeEquipo2->restarVida(2);
			}
		}
		else if(golpesFuertes[animacionPersonaje1] && animacionPersonaje2!="recibirGolpeF"){//personaje1 esta golpeando fuerte
			if(animacionPersonaje2=="defensa"){
				if(tiempoCorriendo) personajeEquipo2->restarVida(1);
			}

			else{
				personajeEquipo2->cambiarAnimacion("recibirGolpeF");
				if (tiempoCorriendo)
					personajeEquipo2->restarVida(4);
			}
		}
		else if(movimientosEspeciales[animacionPersonaje1]){
			int ancho1=personajeEquipo1->obtenerSprite()->getAncho();
			if (ancho1>220){
				ancho1=120;
			}else if(ancho1<=100){
				ancho1=200;
			}
			int ancho2=personajeEquipo1->obtenerSprite()->getAncho();
			int anchoTotal=2.5*(ancho1+ancho2);
			if(personajeEquipo1->getFlip()==SDL_FLIP_NONE){
				personajeEquipo2->serLanzado();
				SDL_Delay(10);
				//personajeEquipo2->forzarPosicion((personajeEquipo2->getPosX())-anchoTotal,personajeEquipo2->getPosY());
			}
			else{
				personajeEquipo1->serLanzado();
				SDL_Delay(10);
				//personajeEquipo2->forzarPosicion((personajeEquipo2->getPosX())+anchoTotal,personajeEquipo2->getPosY());
			}
			personajeEquipo2->cambiarAnimacion("levantarse");
			if(tiempoCorriendo){
				personajeEquipo2->restarVida(6);
			}
		}

		if(golpesSuaves[animacionPersonaje2]&& animacionPersonaje1!="recibirGolpe"){//personaje2 esta golpeando
			if(animacionPersonaje1=="defensa"  ){
				if(tiempoCorriendo) personajeEquipo1->restarVida(1);
			}

			else{
				personajeEquipo1->cambiarAnimacion("recibirGolpe");
				if (tiempoCorriendo)
					personajeEquipo1->restarVida(2);
			}
		}
		else if(golpesFuertes[animacionPersonaje2]&& animacionPersonaje1!="recibirGolpeF"){//personaje2 esta golpeando fuerte
			if(animacionPersonaje1=="defensa" ){
				if(tiempoCorriendo) personajeEquipo1->restarVida(1);
			}
			else{
				personajeEquipo1->cambiarAnimacion("recibirGolpeF");
				if (tiempoCorriendo)
					personajeEquipo1->restarVida(4);
			}
		}else if(movimientosEspeciales[animacionPersonaje2]){
			int ancho1=personajeEquipo2->obtenerSprite()->getAncho();
			if (ancho1>220){
				ancho1=120;
			}else if(ancho1<=100){
				ancho1=200;
			}
			int ancho2=personajeEquipo1->obtenerSprite()->getAncho();
			int anchoTotal=2.5*(ancho1+ancho2);
			if(personajeEquipo2->getFlip()==SDL_FLIP_NONE){
				personajeEquipo1->serLanzado();
				SDL_Delay(10);
				//personajeEquipo1->forzarPosicion((personajeEquipo1->getPosX())-anchoTotal,personajeEquipo1->getPosY());
			}
			else{
				personajeEquipo1->serLanzado();
				SDL_Delay(10);
				//personajeEquipo1->forzarPosicion((personajeEquipo1->getPosX())+anchoTotal,personajeEquipo1->getPosY());
			}
			personajeEquipo1->cambiarAnimacion("levantarse");
			if(tiempoCorriendo){
				personajeEquipo1->restarVida(6);
			}
		}
	}
}
