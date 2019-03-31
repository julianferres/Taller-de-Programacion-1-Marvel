#include <Personaje.hpp>

Personaje::~Personaje(){
}

Personaje::Personaje(ControladorGrafico &graficos,const string filepath, float x, float y){
	this->posx=x;
	this->posy=y;
	this->sprite=Sprite(graficos,filepath,7,20,89,115);

}
void Personaje::dibujar(ControladorGrafico &graficos){
	this->sprite.dibujar(graficos,this->posx,this->posy);
}
void Personaje::MoverDerecha(){
	this->posx=this->posx+30;
}

void Personaje::MoverIzquierda(){
	this->posx=this->posx-30;
}
