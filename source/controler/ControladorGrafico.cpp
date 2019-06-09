#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>

using namespace std;

extern ControladorJson *controladorJson;

ControladorGrafico::ControladorGrafico(int idCliente){
	if(controladorJson->esfullscreen())
		this->sizePantalla = SDL_WINDOW_FULLSCREEN;
	SDL_CreateWindowAndRenderer(controladorJson->anchoVentana(),controladorJson->alturaVentana(), sizePantalla, &this->_window, &this->_renderer);
	string tituloVentana = "Marvel vs Capcom - Jugador "+to_string(idCliente);
	SDL_SetWindowTitle(this->_window,tituloVentana.c_str());
}

ControladorGrafico::~ControladorGrafico(){
	_spriteSheets.clear();
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyWindow(this->_window);
}

void ControladorGrafico::cambiarPantallaCompleta(){
	if (controladorJson->esfullscreen()){
		controladorJson->cambiarPantallaCompleta();
		this->sizePantalla = SDL_WINDOW_RESIZABLE;
	}else{
		controladorJson->cambiarPantallaCompleta();
		this->sizePantalla = SDL_WINDOW_FULLSCREEN;
	}
	SDL_SetWindowFullscreen(this->_window, this->sizePantalla);
}

SDL_Surface* ControladorGrafico::cargarImagen(const string &filePath){
	if(this->_spriteSheets.count(filePath) == 0)
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());

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

void ControladorGrafico::maximizarVentana(int ancho, int alto){
	controladorJson->maximizarVentana(ancho, alto);
}

void ControladorGrafico::dibujarRectanguloDeColor(int red, int green, int blue, int alpha, SDL_Rect *rectangulo){
	SDL_SetRenderDrawColor(this->_renderer, red, green, blue, alpha);
	SDL_RenderFillRect(this->_renderer, rectangulo);
	SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 0);

}
