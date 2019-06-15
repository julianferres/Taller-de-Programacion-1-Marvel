#include <LifeBar.hpp>
#include <stdio.h>
#include "iostream"
using namespace std;

LifeBar::LifeBar(){
}

void LifeBar::setearLados(int *ladosPersonajes){
	lados.insert({"CapitanAmerica", ladosPersonajes[0]});
	lados.insert({"Hulk", ladosPersonajes[1]});
	lados.insert({"Spiderman", ladosPersonajes[2]});
	lados.insert({"Venom", ladosPersonajes[3]});

	if(lados["CapitanAmerica"] == lados["Hulk"]){
		companieros.insert({"CapitanAmerica", "Hulk"});
		companieros.insert({"Hulk", "CapitanAmerica"});
		companieros.insert({"Spiderman", "Venom"});
		companieros.insert({"Venom", "Spiderman"});
		alturas.insert({"CapitanAmerica", 0});
		alturas.insert({"Hulk", 1});
		alturas.insert({"Spiderman", 0});
		alturas.insert({"Venom", 1});
	}

	else if(lados["CapitanAmerica"] == lados["Spiderman"]){
		companieros.insert({"CapitanAmerica", "Spiderman"});
		companieros.insert({"Spiderman", "CapitanAmerica"});
		companieros.insert({"Hulk", "Venom"});
		companieros.insert({"Venom", "Hulk"});
		alturas.insert({"CapitanAmerica", 0});
		alturas.insert({"Hulk", 0});
		alturas.insert({"Spiderman", 1});
		alturas.insert({"Venom", 1});
	}

	else {
		companieros.insert({"CapitanAmerica", "Venom"});
		companieros.insert({"Venom", "CapitanAmerica"});
		companieros.insert({"Hulk", "Spiderman"});
		companieros.insert({"Spiderman", "Hulk"});
		alturas.insert({"CapitanAmerica", 0});
		alturas.insert({"Hulk", 1});
		alturas.insert({"Spiderman", 0});
		alturas.insert({"Venom", 1});
	}
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
