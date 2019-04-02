#include <Personaje.hpp>
#include <ControladorJson.hpp>
#include <string>

extern ControladorJson *controladorJson;

Personaje::~Personaje(){
}
Personaje::Personaje(ControladorGrafico &graficos, std::string nombre){
	this->posx= jugador1::X0;
	this->posy= controladorJson->alturaVentana()*3/4;
	this->alto = controladorJson->alturaPersonaje(nombre);
	this->ancho = controladorJson->anchoPersonaje(nombre);
	this->sprite=Sprite(graficos,controladorJson->pathImagen(nombre),this->getXInicial(nombre),
			this->getYInicial(nombre),ancho,alto);
}

void Personaje::dibujar(ControladorGrafico &graficos){
	this->sprite.dibujar(graficos,this->posx,this->posy);
}

void Personaje::MoverDerecha(){
	if(posx > controladorJson->anchoVentana() - ancho)
		return;
	this->posx=this->posx+10;
}

void Personaje::MoverIzquierda(){
	if(posx < 0)
			return;
	this->posx=this->posx-10;
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

