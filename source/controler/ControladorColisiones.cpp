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
	golpesFuertes["patadaAF"]=1;
	golpesFuertes["golpeAF"]=1;
	golpesFuertes["patadaSaltando"]=1;
	golpesSuaves["patadaA"]=1;
	movimientos["movDerecha"]=1;
	movimientos["movIzquierda"]=1;
	movimientos["salto"]=1;
	movimientos["agacharse"]=1;
	movimientosEspeciales["tirar"]=1;

	offset["Venom"]=15;
	offset["Spiderman"] = 30;
	offset["CapitanAmerica"] = 30;
	offset["Megaman"] = 5;

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

void ControladorColisiones::resolverDisparos(Personaje* personaje1,Personaje* personaje2,bool tiempoCorriendo){
	if(!personaje1->estaDisparando() && !personaje2->estaDisparando()){
		 disparoAcertado1=false;
		 disparoAcertado2=false;
		 return;
	}
	setPersonaje1(personaje1);
	setPersonaje2(personaje2);
	if(personaje1->estaDisparando() &&!disparoAcertado1){
		recPersonaje1=personaje1->getRectDestinoArrojable();
		recPersonaje2=personaje2->obtenerRectangulo();
		if(recPersonaje1.x<recPersonaje2.x){
			recPersonaje1.x-=30;
		}
		else{
			recPersonaje1.x+=30;
		}
		resolverColisiones(tiempoCorriendo);
		if(hayColision()) disparoAcertado1=true;
	}

	if(personaje2->estaDisparando() &&!disparoAcertado2){
		recPersonaje1=personaje1->obtenerRectangulo();
		recPersonaje2=personaje2->getRectDestinoArrojable();
		if(recPersonaje2.x<recPersonaje1.x){
				recPersonaje2.x-=30;
			}
			else{
				recPersonaje2.x+=30;
			}
		resolverColisiones(tiempoCorriendo);
		if(hayColision()) disparoAcertado2=true;
	}



}


void ControladorColisiones::resolverColisiones(bool tiempoCorriendo){
	string animacionPersonaje1 = personajeEquipo1->obtenerSprite()->getAnimacionActual();
	string animacionPersonaje2 = personajeEquipo2->obtenerSprite()->getAnimacionActual();
	moverRectangulo(animacionPersonaje1,animacionPersonaje2);
	if(hayColision()){
		if(golpesSuaves[animacionPersonaje1]&& animacionPersonaje2!="recibirGolpe" && animacionPersonaje2!="recibirGolpe" && animacionPersonaje2!="levantarse" && animacionPersonaje2!="defensa" ){//personaje1 esta golpeando
			personajeEquipo2->cambiarAnimacion("recibirGolpe");
			if (tiempoCorriendo)
				personajeEquipo2->restarVida(2);

		}
		else if(golpesFuertes[animacionPersonaje1] && animacionPersonaje2!="recibirGolpeF"&& animacionPersonaje2!="recibirGolpe" && animacionPersonaje2!="levantarse" && animacionPersonaje2!="defensa" ){//personaje1 esta golpeando fuerte

			personajeEquipo2->cambiarAnimacion("recibirGolpeF");
			if (tiempoCorriendo)
				personajeEquipo2->restarVida(4);

		}
		else if(movimientosEspeciales[animacionPersonaje1] && animacionPersonaje2!="serLanzado"&& animacionPersonaje2!="levantarse"){
			if(tiempoCorriendo){
				personajeEquipo2->restarVida(6);
			}
			personajeEquipo2->serLanzado(personajeEquipo1);
			}

		if(golpesSuaves[animacionPersonaje2]&& animacionPersonaje1!="recibirGolpe"&& animacionPersonaje1!="recibirGolpe" && animacionPersonaje1!="levantarse" && animacionPersonaje1!="defensa" ){//personaje2 esta golpeando

			personajeEquipo1->cambiarAnimacion("recibirGolpe");
			if (tiempoCorriendo)
				personajeEquipo1->restarVida(2);

		}
		else if(golpesFuertes[animacionPersonaje2]&& animacionPersonaje1!="recibirGolpeF"&& animacionPersonaje1!="recibirGolpe" && animacionPersonaje1!="levantarse" && animacionPersonaje1!="defensa" ){//personaje2 esta golpeando fuerte

			personajeEquipo1->cambiarAnimacion("recibirGolpeF");
			if (tiempoCorriendo)
				personajeEquipo1->restarVida(4);

		}else if(movimientosEspeciales[animacionPersonaje2]&& animacionPersonaje1!="serLanzado"&& animacionPersonaje1!="levantarse"){
			if(tiempoCorriendo){
				personajeEquipo1->restarVida(6);
			}
			personajeEquipo1->serLanzado(personajeEquipo2);
		}
	}
}


void ControladorColisiones::moverRectangulo(string animacionPersonaje1, string animacionPersonaje2){

	if(recPersonaje1.x<recPersonaje2.x){//personaje 1 a la izq
		recPersonaje1.x-=offset[personajeEquipo2->getNombre()];
	}
	else if(recPersonaje1.x>recPersonaje2.x){//personaje 1 a la der
		recPersonaje1.x+=offset[personajeEquipo2->getNombre()];
	}

	if(recPersonaje2.x<recPersonaje1.x){//personaje 2 a la izq
		recPersonaje2.x-=offset[personajeEquipo1->getNombre()];
	}
	else if(recPersonaje2.x>recPersonaje1.x){//personaje 2a la der
		recPersonaje2.x+=offset[personajeEquipo1->getNombre()];
	}



}
