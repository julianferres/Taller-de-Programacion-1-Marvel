#include <Personaje.hpp>
#include <ControladorJson.hpp>
#include <string>
#include <iostream>
#include<math.h>
#define constanteDeAltura 39.2f //Viene de despejar la velocidad en funcion a una h_max = 2*alto
#define constanteTiempoCiclos 0.3
using namespace std;

Personaje::~Personaje(){
}

Personaje::Personaje(ControladorGrafico &graficos, string nombre){
	this->posx= controladorJson->posicionXinicialPersonaje(nombre);
	this->posxrelativo=this->posx;
	this->posy= controladorJson->alturaVentana()*3/4;
	this->alto = controladorJson->alturaPersonaje(nombre);
	this->ancho = controladorJson->anchoPersonaje(nombre);
	//this->sprite=Sprite(graficos,controladorJson->pathImagen(nombre),this->getXInicial(nombre),this->getYInicial(nombre),ancho,alto);
	this->spriteAnimado=SpriteAnimado(graficos,controladorJson->pathImagen(nombre));
	this->spriteAnimado.cargarAnimaciones(nombre);
	this->spriteAnimado.iniciarAnimacion("quieto");
	this->velocidadInicial = sqrt(constanteDeAltura * alto);
}

void Personaje::dibujar(ControladorGrafico &graficos){
	if(saltando)
		this->Saltar();
	//this->sprite.dibujar(graficos,this->posx,this->posy);
	this->spriteAnimado.update(10);
	if(this->spriteAnimado.getAnimacionActual()=="movDerecha"){
		if(this->posxrelativo<this->posx){
			this->spriteAnimado.dibujar(graficos,this->posxrelativo,this->posy);
			this->posxrelativo=this->posxrelativo+5;
		}
	}
	else{
		if(this->spriteAnimado.getAnimacionActual()=="movIzquierda"){
			if(this->posxrelativo>this->posx){
				this->spriteAnimado.dibujar(graficos,this->posxrelativo,this->posy);
				this->posxrelativo=this->posxrelativo-5;
			}
		}
		else{
			this->spriteAnimado.dibujar(graficos,this->posx,this->posy);
		}
	}
}

void Personaje::MoverDerecha(){
	if(posx > controladorJson->anchoVentana() - ancho)
		return;
	this->spriteAnimado.iniciarAnimacion("movDerecha");
	this->posxrelativo=this->posx;
	this->posx=this->posx+30;
}

void Personaje::MoverIzquierda(){
	if(posx < 0)
			return;
	this->spriteAnimado.iniciarAnimacion("movIzquierda");
	this->posxrelativo=this->posx;
	this->posx=this->posx-30;
}
void Personaje::agacharse(){
	this->spriteAnimado.iniciarAnimacion("agacharse");
}

void Personaje::Saltar(){
	this->spriteAnimado.iniciarAnimacion("salto");
	if( ! saltando) saltando = true;
	else{
		if(alturaActualSalto <= 0 && tiempo != 0 ){
			saltando = false; 	tiempo = 0; 	return;
		}
		else{
			tiempo += constanteTiempoCiclos;
			float alturaPrevia  = alturaActualSalto;
			alturaActualSalto = (velocidadInicial - 4.9* tiempo)*tiempo;
			//El 4.9 viene de 0.5*gravedad
			posy -= (alturaActualSalto - alturaPrevia);
		}
	}
}


int Personaje::getXInicial(std::string nombre){
	if( nombre == "CapitanAmerica"){
		return 7;
	}else if (nombre == "Spiderman"){
		return 11;
	}else{
		return 1;
	}
}

int Personaje::getYInicial(std::string nombre){
	if( nombre == "CapitanAmerica"){
		return 20;
	}else if (nombre == "Spiderman"){
		return 11;
	}else{
		return 1;
	}
}

float Personaje::getX(){
	return this->posx;
}

float Personaje::getXDer(){
	return (this->posx + this->ancho);
}

