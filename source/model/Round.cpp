#include <Round.hpp>

extern ControladorJson *controladorJson;

Round::Round(int num){
	this->numero = num;
	this->parallax = new Parallax(this->numero);
	this->tiempo = new Temporizador();
	this->terminado = false;
}

Round::~Round(){

}

Parallax* Round::getParallax(){
	return this->parallax;
}

int Round::getNumero(){

	return this->numero;
}

void Round::iniciarTiempo(){
	this->tiempo->resetear();
}

bool Round::finalizado(){
	return (this->tiempo->getDeltaTiempo() >= controladorJson->TIEMPO_ROUND || this->terminado);
}

void Round::actualizarTiempo(){
	this->tiempo->actualizar();
}

void Round::frenarTiempo(){
	this->tiempo->frenar();
}

void Round::reiniciarTiempo(){
	this->tiempo->recuperar();
}

std::tuple<std::string,SDL_Rect, SDL_Rect ,SDL_RendererFlip > Round::getTiempoDibujable(){
	return this->tiempo->getDibujable();
}
std::tuple<std::string,SDL_Rect, SDL_Rect ,SDL_RendererFlip > Round::getMundoDibujable(){
	return this->tiempo->getDibujableMundo();
}

std::tuple<std::string,SDL_Rect, SDL_Rect ,SDL_RendererFlip > Round::dibujarBanner(){
	std::tuple<std::string,SDL_Rect, SDL_Rect ,SDL_RendererFlip > dibujable;
	SDL_Rect source  = {-1,-1,-1,-1};
	SDL_Rect dest = {0,0,controladorJson->anchoVentana(), controladorJson->alturaVentana()};
	dibujable = std::make_tuple("Banner" + std::to_string(this->numero), source, dest, SDL_FLIP_NONE);
	return dibujable;
}

void Round::finalizar(){
	this->terminado = true;
}
