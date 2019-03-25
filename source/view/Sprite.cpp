/*
 * Srprite.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: luupesado
 */


#include <Sprite.hpp>
#include <ControladorGrafico.hpp>
#include <ConfiguracionGlobal.hpp>
using namespace std;
Sprite::Sprite() {};

Sprite::Sprite( ControladorGrafico &graficos, const string &filePath, int x0, int y0, int ancho, int alto,
		float posX, float posY):
					_x(posX),
					_y(posY){
	this->_rectanguloOrigen.x = x0;
	this->_rectanguloOrigen.y = y0;
	this->_rectanguloOrigen.w = ancho;
	this->_rectanguloOrigen.h = alto;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graficos.getRenderer(),graficos.cargarImagen(filePath));
	if (this->_spriteSheet == NULL){
		printf("\nError: Unable to load image\n");
	}
}

void Sprite::dibujar(ControladorGrafico &graficos, int x, int y){
	SDL_Rect rectanguloDestino = {x, y, this->_rectanguloOrigen.w * globals::ESCALA_SPRITE, this->_rectanguloOrigen.h * globals::ESCALA_SPRITE};
	graficos.dibujarImagen(this->_spriteSheet, &this->_rectanguloOrigen, &rectanguloDestino);
}

void Sprite::update(){};

Sprite::~Sprite(){};

//hgjh
