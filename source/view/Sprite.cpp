#include <Sprite.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ConfiguracionGlobal.hpp>
using namespace std;
Sprite::Sprite() {};
Sprite::~Sprite(){};

Sprite::Sprite( ControladorGrafico &graficos, const string &filePath, int x0, int y0, int ancho, int alto,
		float posX, float posY):_x(posX),_y(posY){
	this->_rectanguloOrigen.x = x0;
	this->_rectanguloOrigen.y = y0;
	this->_rectanguloOrigen.w = ancho;
	this->_rectanguloOrigen.h = alto;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graficos.getRenderer(),graficos.cargarImagen(filePath));
	}

void Sprite::dibujar(ControladorGrafico &graficos, int x, int y){
	SDL_Rect rectanguloDestino = {x, y, this->_rectanguloOrigen.w, this->_rectanguloOrigen.h};
	graficos.dibujarImagen(this->_spriteSheet, &this->_rectanguloOrigen, &rectanguloDestino);
}

void Sprite::update(){};



