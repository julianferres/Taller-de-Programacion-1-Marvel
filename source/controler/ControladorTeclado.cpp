#include <ControladorTeclado.hpp>

void ControladorTeclado::empezarNuevoFrame(){
	this->_teclasPresionadas.clear();
	this->_teclasSoltadas.clear();

}


void ControladorTeclado::eventoPresionarTecla(const SDL_Event& evento){
	this->_teclasPresionadas[evento.key.keysym.scancode] = true;
	this->_teclasSostenidas[evento.key.keysym.scancode] = true;

}

void ControladorTeclado::eventoSoltarTecla(const SDL_Event& evento){
	this->_teclasSoltadas[evento.key.keysym.scancode] = true;
	this->_teclasSostenidas[evento.key.keysym.scancode] = false;
}

bool ControladorTeclado::sePresionoUnaTecla(SDL_Scancode tecla){
	return this->_teclasPresionadas[tecla];
}

bool ControladorTeclado::seSoltoUnaTecla(SDL_Scancode tecla){
	return this->_teclasSoltadas[tecla];
}

bool ControladorTeclado::seEstaPresionandoUnaTecla(SDL_Scancode tecla){
	return this->_teclasSostenidas[tecla];
}
