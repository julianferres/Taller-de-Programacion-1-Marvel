#include <Round.hpp>

Round::Round(int num){
	this->numero = num;
	this->parallax = new Parallax(this->numero);
	this->tiempo = new Temporizador();
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
	return this->tiempo->getDeltaTiempo() >= 99;
}
