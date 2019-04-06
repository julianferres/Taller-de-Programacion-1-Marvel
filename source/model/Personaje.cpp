#include <Personaje.hpp>
#include <ControladorJson.hpp>
#include <string>
#include<math.h>

#define constanteDeAltura 39.2f //Viene de despejar la velocidad en funcion a una h_max = 2*alto
#define constanteTiempoCiclos 0.3
using namespace std;

Personaje::~Personaje(){
}

Personaje::Personaje(ControladorGrafico &graficos, string nombre, int posicionXinicial){
	this->posx= posicionXinicial;
	this->posxrelativo=this->posx;
	this->alto = controladorJson->alturaPersonaje(nombre);
	this->ancho = controladorJson->anchoPersonaje(nombre);
	this->posy= controladorJson->alturaVentana() - alto - 50;
	this->spriteAnimado=SpriteAnimado(graficos,controladorJson->pathImagen(nombre));
	this->spriteAnimado.cargarAnimaciones(nombre);
	this->spriteAnimado.iniciarAnimacion("quieto");
	this->velocidadInicial = sqrt(constanteDeAltura * alto);
}

void Personaje::dibujar(ControladorGrafico &graficos){
	if(saltando)
		this->Saltar();
	this->spriteAnimado.update();
	if(this->spriteAnimado.getAnimacionActual()=="movDerecha"){
		if(this->posxrelativo<this->posx){
			this->spriteAnimado.dibujar(graficos,this->posxrelativo,this->posy,alto,ancho);
			this->posxrelativo=this->posxrelativo+1;
		}
	}
	else{
		if(this->spriteAnimado.getAnimacionActual()=="movIzquierda"){
			if(this->posxrelativo>this->posx){
				this->spriteAnimado.dibujar(graficos,this->posxrelativo,this->posy,alto, ancho);
				this->posxrelativo=this->posxrelativo-1;
			}
		}
		else{
			this->spriteAnimado.dibujar(graficos,this->posx,this->posy,alto, ancho);
		}
	}
}

void Personaje::MoverDerecha(){
	if(posx > controladorJson->anchoVentana() - ancho )
		return;
	if(!saltando)
		this->spriteAnimado.iniciarAnimacion("movDerecha");
	this->posxrelativo=this->posx;
	this->posx=this->posx+50;
}

void Personaje::MoverIzquierda(){
	if(posx < 0)
			return;
	if(!saltando)
		this->spriteAnimado.iniciarAnimacion("movIzquierda");
	this->posxrelativo=this->posx;
	this->posx=this->posx-50;
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

float Personaje::getX(){
	return this->posx;
}

float Personaje::getXDer(){
	return (this->posx + this->ancho);
}

