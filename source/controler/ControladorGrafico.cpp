#include <ControladorGrafico.hpp>
#include <SDL2/SDL.h>
#include <ConfiguracionGlobal.hpp>
#include <iostream>
using namespace globals;
using namespace std;


ControladorGrafico::ControladorGrafico(){
	SDL_CreateWindowAndRenderer(ANCHO_DE_PANTALLA,ALTO_DE_PANTALLA, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Marvel vs Capcom");
}

ControladorGrafico::~ControladorGrafico(){
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
	SDL_Quit();
	cout << "Juego finalizado!" <<endl;
}

SDL_Surface* ControladorGrafico::cargarImagen(const string &filePath){
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

void ControladorGrafico::limpiar(){
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* ControladorGrafico::getRenderer() const{
	return this->_renderer;
}


