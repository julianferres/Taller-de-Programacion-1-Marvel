#include <Personaje.hpp>

Personaje::Personaje(ControladorGrafico &graphics, float x, float y):
	SpriteAnimado(graphics, "contents/images/CaptainAmericaSprites.png", 0, 0, 16, 16, x, y, 100){
	graphics.cargarImagen("contents/images/CaptainAmericaSprites.png");
	this->configurarAnimaciones();
}
/*{
	objTexture = ControladorTexturas::LoadTexture(imagen);
	xpos = x;
	ypos = y;

}*/

void Personaje::update(){
/*
	srcRect.h = 286;
	srcRect.w = 256;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w ;
	destRect.h = srcRect.h;*/

}
void Personaje::configurarAnimaciones(){
	this->agregarAnimacion(1, 0, 0, "IdleLeft", 16, 16, Vector2(0,0));
	this->agregarAnimacion(1, 0, 16, "IdleRight", 16, 16, Vector2(0,0));
	this->agregarAnimacion(3, 0, 0, "RunLeft", 16, 16, Vector2(0,0));
	this->agregarAnimacion(3, 0, 16, "RunRight", 16, 16, Vector2(0,0));
}


void Personaje::MoverDerecha(){
	this->_dx = constantes_personajes::VELOCIDAD;
	this->iniciarAnimacion("RunRight");
	//this->_facing = RIGHT;
}

void Personaje::MoverIzquierda(){
	this->_dy = constantes_personajes::VELOCIDAD;
	this->iniciarAnimacion("RunLeft");
}
/*

void Personaje::Render(){
	SDL_RenderCopy(Juego::renderer, objTexture, &srcRect, &destRect);
}*/

