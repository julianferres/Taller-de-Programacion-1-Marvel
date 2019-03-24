/*
 * ControladorGrafico.cpp
 *
 *  Created on: Mar 23, 2019
 *      Author: luupesado
 */

#include <ControladorGrafico.hpp>
#include <SDL2/SDL.h>
#include <ConfiguracionGlobal.hpp>
/*Graphic class
 *Holds all the information dealing with graphics for the game
 */

ControladorGrafico::ControladorGrafico(){
	SDL_CreateWindowAndRenderer(globals::ANCHO_DE_PANTALLA, globals::ALTO_DE_PANTALLA, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Cavestory");
}

ControladorGrafico::~ControladorGrafico(){
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface* ControladorGrafico::cargarImagen(const std::string &filePath){
	if(this->_spriteSheets.count(filePath) == 0){
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}

void ControladorGrafico::dibujarImagen(SDL_Texture* textura, SDL_Rect* rectanguloOrigen, SDL_Rect* rectanguloDestino){
	SDL_RenderCopy(this->_renderer, textura, rectanguloOrigen, rectanguloDestino);
}

void ControladorGrafico::render(){
	SDL_RenderPresent(this->_renderer);
}

void ControladorGrafico::clear(){
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* ControladorGrafico::getRenderer() const{
	return this->_renderer;
}


