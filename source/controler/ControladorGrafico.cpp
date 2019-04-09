#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>

using namespace std;

extern ControladorJson *controladorJson;

ControladorGrafico::ControladorGrafico(){
	SDL_CreateWindowAndRenderer(controladorJson->anchoVentana(),controladorJson->alturaVentana(), SDL_WINDOW_RESIZABLE, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Marvel vs Capcom");
}

ControladorGrafico::~ControladorGrafico(){
	SDL_DestroyWindow(this->_window);
	SDL_DestroyRenderer(this->_renderer);
	SDL_Quit();
}

SDL_Surface* ControladorGrafico::cargarImagen(const string &filePath){
	if(this->_spriteSheets.count(filePath) == 0){
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}

void ControladorGrafico::dibujarImagen(SDL_Texture* textura, SDL_Rect* rectanguloOrigen, SDL_Rect* rectanguloDestino, SDL_RendererFlip flip){
	SDL_RenderCopyEx(this->_renderer, textura, rectanguloOrigen, rectanguloDestino,0,NULL, flip);
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

bool ControladorGrafico::controlarColision(SDL_Rect rect1,SDL_Rect rect2){
	if(rect1.y >= rect2.y + rect2.h)
		return false;
	if(rect1.x >= rect2.x + rect2.w)
		return false;
	if(rect1.y + rect1.h <= rect2.y)
		return false;
	if(rect1.x + rect1.w <= rect2.x)
		return false;
	return true;

}
