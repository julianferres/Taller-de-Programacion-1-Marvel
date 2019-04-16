#include <ControladorTeclado.hpp>

ControladorTeclado::~ControladorTeclado(){
	_heldKeys.clear();
	_pressedKeys.clear();
	_releasedKeys.clear();
}

void ControladorTeclado::reiniciar(){
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}

void ControladorTeclado::eventoPresionarTecla(const SDL_Event& evento){
	this->_pressedKeys[evento.key.keysym.scancode] = true;
	this->_heldKeys[evento.key.keysym.scancode] = true;
}

void ControladorTeclado::eventoSoltarTecla(const SDL_Event& evento){
	this->_releasedKeys[evento.key.keysym.scancode] = true;
	this->_heldKeys[evento.key.keysym.scancode] = false;
}

bool ControladorTeclado::sePresionoUnaTecla(SDL_Scancode tecla){
	return this->_pressedKeys[tecla];
}

bool ControladorTeclado::seSoltoUnaTecla(SDL_Scancode tecla){
	return this->_releasedKeys[tecla];
}

bool ControladorTeclado::seEstaPresionandoUnaTecla(SDL_Scancode tecla){
	return this->_heldKeys[tecla];
}
