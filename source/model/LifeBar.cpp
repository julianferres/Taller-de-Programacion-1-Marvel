#include <LifeBar.hpp>
#include <stdio.h>
#include "iostream"
using namespace std;

LifeBar::LifeBar(){
	lados.insert({"CapitanAmerica", 0});
	lados.insert({"Hulk", 0});
	lados.insert({"Spiderman", 1});
	lados.insert({"Venom", 1});

	alturas.insert({"CapitanAmerica", 0});
	alturas.insert({"Hulk", 1});
	alturas.insert({"Spiderman", 0});
	alturas.insert({"Venom", 1});

	companieros.insert({"CapitanAmerica", "Hulk"});
	companieros.insert({"Hulk", "CapitanAmerica"});
	companieros.insert({"Spiderman", "Venom"});
	companieros.insert({"Venom", "Spiderman"});
}

void LifeBar::setearAnchoyAltoPantalla(int altoVentana, int anchoVentana){
	this->alturaVentana = altoVentana;
	this->anchoVentana = anchoVentana;
}

string LifeBar::obtenerPath(string nombrePersonaje){
	return ("contents/images/"+nombrePersonaje+"-lb.png");
}

string LifeBar::obtenerNombreBarra(string nombrePersonaje){
	return (nombrePersonaje+"-lb");
}

int LifeBar::obtenerAnchoBarra(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return this->alturaVentana / 10;
	return (this->alturaVentana * 4) / 60;
}

int LifeBar::obtenerLargoBarra(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return (this->anchoVentana / 3);
	return (this->anchoVentana / 4);
}

int LifeBar::obtenerPosicionHorizontal(string nombrePersonaje){
	if(lados[nombrePersonaje] == 0) return (this->anchoVentana / 120);
	return this->anchoVentana - obtenerLargoBarra(nombrePersonaje) - this->anchoVentana / 120;
}

int LifeBar::obtenerPosicionVertical(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return this->alturaVentana / 70;
	return (this->alturaVentana * 9) / 70;
}

SDL_RendererFlip LifeBar::obtenerFlipBarra(string nombrePersonaje){
	if(lados[nombrePersonaje] == 0) return SDL_FLIP_HORIZONTAL;
	return SDL_FLIP_NONE;
}



int LifeBar::obtenerAnchoFondoVida(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return this->alturaVentana / 19;
	return (this->alturaVentana * 4) / (6 * 19);
}

int LifeBar::obtenerLargoFondoVida(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return (16 * this->anchoVentana) / 60;
	return (this->anchoVentana*48) / 240;
}

int LifeBar::obtenerPosicionHorizontalFondoVida(string nombrePersonaje){
	if(lados[nombrePersonaje] == 0){
		if(alturas[nombrePersonaje] == 0) return (this->anchoVentana * 15) / 240;
		return (45*this->anchoVentana) /920;
	}
	else{
		if(alturas[nombrePersonaje] == 0) return this->anchoVentana - obtenerLargoFondoVida(nombrePersonaje) - (this->anchoVentana * 15) / 240;
		return this->anchoVentana - obtenerLargoFondoVida(nombrePersonaje) - (45*this->anchoVentana) /920;
	}
}

int LifeBar::obtenerPosicionVerticalFondoVida(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 0) return (5*this->alturaVentana / 240);
	return (this->alturaVentana*9) / 70;
}

int LifeBar::obtenerPosicionHorizontalVida(string nombrePersonaje, int vida){
	if(lados[nombrePersonaje] == 0){
			if(alturas[nombrePersonaje] == 0) return (this->anchoVentana * 15) / 240;
			return (45*this->anchoVentana) /920;
		}
	else{
		if(alturas[nombrePersonaje] == 0) return (this->anchoVentana - obtenerLargoFondoVida(nombrePersonaje) - (this->anchoVentana * 15) / 240) + ((obtenerLargoFondoVida(nombrePersonaje) * (100-vida)) / 100);
		return this->anchoVentana - obtenerLargoFondoVida(nombrePersonaje) - (45*anchoVentana) /920 + ((obtenerLargoFondoVida(nombrePersonaje) * (100 - vida)) / 100);
	}
}

void LifeBar::actualizarPersonajesActuales(string nombrePersonaje){
	if(alturas[nombrePersonaje] == 1) {
		alturas[nombrePersonaje] = 0;
		alturas[companieros[nombrePersonaje]] = 1;
	}

}
