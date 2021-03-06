#include <Animacion.hpp>
#include <string>

Animacion::Animacion(std::string Nombre, int Frames,int x,int y, int ancho, int alto,int Velocidad ){
	this->nombre = Nombre;
	this->frames = Frames;
	this->velocidad = Velocidad;
	this->alto = alto;
	this->ancho = ancho;
	for (int i = 0; i < frames; i++){
		SDL_Rect newRect = { x+(i*ancho), y, ancho, alto};
		rectangulos.push_back(newRect);
	}
}

std::string Animacion::getNombre(){
	return nombre;
}

int Animacion::getFrames(){
	return frames;
}

SDL_Rect Animacion::getRectOrigen(int frameIndex){
	return rectangulos[frameIndex];
}

int Animacion::getVelocidad(){
	return velocidad;
}

int Animacion::getAlto(){
	return this->alto;
}

int Animacion::getAncho(){
	return this->ancho;
}

