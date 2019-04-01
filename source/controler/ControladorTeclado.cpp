#include <ControladorTeclado.hpp>

void ControladorTeclado::beginNewFrame(){
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}


void ControladorTeclado::keyDownEvent(const SDL_Event& evento){
	this->_pressedKeys[evento.key.keysym.scancode] = true;
	this->_heldKeys[evento.key.keysym.scancode] = true;
}

void ControladorTeclado::keyUpEvent(const SDL_Event& evento){
	this->_releasedKeys[evento.key.keysym.scancode] = true;
	this->_heldKeys[evento.key.keysym.scancode] = false;
}

bool ControladorTeclado::wasKeyPressed(SDL_Scancode tecla){
	return this->_pressedKeys[tecla];
}

bool ControladorTeclado::wasKeyReleased(SDL_Scancode tecla){
	return this->_releasedKeys[tecla];
}

bool ControladorTeclado::isKeyHeld(SDL_Scancode tecla){
	return this->_heldKeys[tecla];
}
