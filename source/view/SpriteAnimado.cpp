/*
 * SpriteAnimado.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: luupesado
 */
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>
#include <Sprite.hpp>
/*
 * Animations for our sprites
 */

SpriteAnimado::SpriteAnimado(){}

SpriteAnimado::SpriteAnimado(ControladorGrafico &graficos, const std::string &filePath, int x0, int y0,
		int ancho, int alto, float posX, float posY, float timeToUpdate):
				Sprite(graficos, filePath, x0, y0, ancho, alto, posX, posY),
				_frameIndex(0),
				_timeToUpdate(timeToUpdate),
				_visible(true),
				_animacionActualUnica(false),
				_animacionActual(""),
				tiempoTrancurrido(0)	{}

void SpriteAnimado::agregarAnimacion(int frames, int x, int y, std::string nombre, int ancho, int alto, Vector2 offset){
	std::vector<SDL_Rect> rectangulos;
	for (int i = 0; i < frames; i++){
		SDL_Rect newRect = { (i + x) * ancho, y, ancho, alto};
		rectangulos.push_back(newRect);
	}
	this->_animaciones.insert(std::pair<std::string, std::vector<SDL_Rect> > (nombre, rectangulos));
	this->_offsets.insert(std::pair<std::string, Vector2> (nombre, offset));

}

void SpriteAnimado::reiniciarAnimacion(){
	this->_animaciones.clear();
	this->_offsets.clear();
}

void SpriteAnimado::iniciarAnimacion(std::string animacion, bool unica){
	this->_animacionActualUnica = unica;
	if(this->_animacionActual != animacion){
		this->_animacionActual = animacion;
		this->_frameIndex = 0;
	}
}

void SpriteAnimado::esVisible(bool visible){
	this->_visible = visible;
}

void SpriteAnimado::pararAnimacion(){
	this->_frameIndex = 0;
	this->animacionFinalizada(this->_animacionActual);
}

void SpriteAnimado::update(int elapsedTime){
	Sprite::update();

	this->tiempoTrancurrido += elapsedTime;
	if(this->tiempoTrancurrido > this->_timeToUpdate){
		this->tiempoTrancurrido -=this->_timeToUpdate;
		if(this->_frameIndex < this->_animaciones[this->_animacionActual].size() - 1){
			this-> _frameIndex++;
		}
		else{
			if(this->_animacionActualUnica == true){
				this->esVisible(false);
			}
			this->_frameIndex = 0;
			this->animacionFinalizada(this->_animacionActual);
		}
	}
}

void SpriteAnimado::dibujar(ControladorGrafico &graficos, int x, int y){
	if(this->_visible){
		SDL_Rect rectanguloDestino;
		rectanguloDestino.x = x + this->_offsets[this->_animacionActual].x;
		rectanguloDestino.y = y + this->_offsets[this->_animacionActual].y;
		rectanguloDestino.w = this->_rectanguloOrigen.w * globals::ESCALA_SPRITE;
		rectanguloDestino.h = this->_rectanguloOrigen.h * globals::ESCALA_SPRITE;

		SDL_Rect sourceRect = this->_animaciones[this->_animacionActual][this->_frameIndex];
		graficos.dibujarImagen(this->_spriteSheet, &sourceRect, &rectanguloDestino);
	}
}

void SpriteAnimado::animacionFinalizada(std::string currentAnimation){

}



