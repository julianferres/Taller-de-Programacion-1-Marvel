#include <LifeBar.hpp>
#include <stdio.h>
#include "iostream"
#include <vector>
using namespace std;

LifeBar::LifeBar(){
}

void LifeBar::setearLados(string *ladosPersonajes){
	personajes[0] = ladosPersonajes[0];
	personajes[1] = ladosPersonajes[1];
	personajes[2] = ladosPersonajes[2];
	personajes[3] = ladosPersonajes[3];

	lados.insert({ladosPersonajes[0], 0});
	lados.insert({ladosPersonajes[1], 0});
	lados.insert({ladosPersonajes[2], 1});
	lados.insert({ladosPersonajes[3], 1});

	companieros.insert({ladosPersonajes[0], ladosPersonajes[1]});
	companieros.insert({ladosPersonajes[1], ladosPersonajes[0]});
	companieros.insert({ladosPersonajes[2], ladosPersonajes[3]});
	companieros.insert({ladosPersonajes[3], ladosPersonajes[2]});

	alturas.insert({ladosPersonajes[0], 0});
	alturas.insert({ladosPersonajes[1], 1});
	alturas.insert({ladosPersonajes[2], 0});
	alturas.insert({ladosPersonajes[3], 1});
}

void LifeBar::setearAnchoyAltoPantalla(int altoVentana, int anchoVentana){
	this->alturaVentana = altoVentana;
	this->anchoVentana = anchoVentana;
	anchoBarraArriba = altoVentana/10;
	anchoBarraAbajo = (altoVentana * 4) / 60;
	largoBarraArriba = anchoVentana / 3;
	largoBarraAbajo = anchoVentana / 4;
	posicionHorizontalBarraIzq = (anchoVentana / 120);
	posicionVerticalBarraArriba = (altoVentana / 70);
	posicionVerticalBarraAbajo = (altoVentana * 9) / 70;

	anchoFondoVidaArriba = altoVentana / 19;
	anchoFondoVidaAbajo = (altoVentana * 4) / (6 * 19);
	largoFondoVidaArriba = (16 * anchoVentana) / 60;
	largoFondoVidaAbajo =  (anchoVentana * 48) / 240;
	posicionVerticalFondoVidaArriba = (5 * altoVentana / 240);
	posicionVerticalFondoVidaAbajo = (altoVentana * 9) / 70;
	posicionHorizontalFondoVidaArribaIzq = (anchoVentana * 15) / 240;
	posicionHorizontalFondoVidaAbajoIzq = (45 * anchoVentana) / 920;

	posicionHorizontalVidaArribaIzq = (anchoVentana * 15) / 240;
	posicionHorizontalVidaAbajoIzq = (45 * anchoVentana) /920;

}

string LifeBar::obtenerPath(string nombrePersonaje){
	return ("contents/images/"+nombrePersonaje+"-lb.png");
}

string LifeBar::obtenerNombreBarra(string nombrePersonaje){
	return (nombrePersonaje+"-lb");
}

int LifeBar::obtenerAnchoBarra(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return anchoBarraArriba;
	return anchoBarraAbajo;
}

int LifeBar::obtenerLargoBarra(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return largoBarraArriba;
	return largoBarraAbajo;
}

int LifeBar::obtenerPosicionHorizontal(string nombrePersonaje){
	if(lados[nombrePersonaje] == 0) return posicionHorizontalBarraIzq;
	return this->anchoVentana - obtenerLargoBarra(nombrePersonaje) - posicionHorizontalBarraIzq;
}

int LifeBar::obtenerPosicionVertical(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return posicionVerticalBarraArriba;
	return posicionVerticalBarraAbajo;
}

SDL_RendererFlip LifeBar::obtenerFlipBarra(string nombrePersonaje){
	if(lados[nombrePersonaje] == 0) return SDL_FLIP_HORIZONTAL;
	return SDL_FLIP_NONE;
}

int LifeBar::obtenerAnchoFondoVida(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return anchoFondoVidaArriba;
	return anchoFondoVidaAbajo;
}

int LifeBar::obtenerLargoFondoVida(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return largoFondoVidaArriba;
	return largoFondoVidaAbajo;
}

int LifeBar::obtenerPosicionHorizontalFondoVida(string nombrePersonaje){
	if(lados[nombrePersonaje] == 0){
		if(alturas[nombrePersonaje] == 0) return posicionHorizontalFondoVidaArribaIzq;
		return posicionHorizontalFondoVidaAbajoIzq;
	}
	else{
		if(alturas[nombrePersonaje] == 0) return this->anchoVentana - obtenerLargoFondoVida(nombrePersonaje) - posicionHorizontalFondoVidaArribaIzq;
		return this->anchoVentana - obtenerLargoFondoVida(nombrePersonaje) - posicionHorizontalFondoVidaAbajoIzq;
	}
}

int LifeBar::obtenerPosicionVerticalFondoVida(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return posicionVerticalFondoVidaArriba;
	return posicionVerticalFondoVidaAbajo;
}

int LifeBar::obtenerPosicionHorizontalVida(string nombrePersonaje, int vida){
	if(lados[nombrePersonaje] == 0){
			if(alturas[nombrePersonaje] == 0) return posicionHorizontalVidaArribaIzq;
			return posicionHorizontalVidaAbajoIzq;
		}
	else{
		if(alturas[nombrePersonaje] == 0) return (this->anchoVentana - obtenerLargoFondoVida(nombrePersonaje) - posicionHorizontalVidaArribaIzq) + ((obtenerLargoFondoVida(nombrePersonaje) * (100-vida)) / 100);
		return this->anchoVentana - obtenerLargoFondoVida(nombrePersonaje) - posicionHorizontalVidaAbajoIzq + ((obtenerLargoFondoVida(nombrePersonaje) * (100 - vida)) / 100);
	}
}

void LifeBar::actualizarPersonajesActuales(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 1) {
		alturas[nombrePersonaje] = 0;
		alturas[companieros[nombrePersonaje]] = 1;
	}
}

string LifeBar::obtenerNombre(int indice){
	return personajes[indice];
}
