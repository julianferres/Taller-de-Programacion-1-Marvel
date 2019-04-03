#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>
#include <Sprite.hpp>

using namespace std;

SpriteAnimado::SpriteAnimado(){
}

SpriteAnimado::SpriteAnimado(ControladorGrafico &graficos, const string &filePath){
	this->spriteSheet = SDL_CreateTextureFromSurface(graficos.getRenderer(),graficos.cargarImagen(filePath));
	this->visible=true;
	this->frameIndex=0;
}

void SpriteAnimado::agregarAnimacion(int frames, int x, int y, string nombre, int ancho, int alto){
	vector<SDL_Rect> rectangulos;
	this->alto=alto;
	this->ancho=ancho;
	for (int i = 0; i < frames; i++){
		SDL_Rect newRect = { x+(i*ancho)-4, y, ancho, alto};
		rectangulos.push_back(newRect);
	}
	this->animacion.insert(pair<string, vector<SDL_Rect> > (nombre, rectangulos));

}

void SpriteAnimado::reiniciarAnimacion(){
	/*this->_animaciones.clear();
	this->_offsets.clear();*/
}

void SpriteAnimado::iniciarAnimacion(string animacion, bool unica){
	this->animacionActualUnica = unica;
	if(this->animacionActual != animacion){
		this->animacionActual = animacion;
		this->frameIndex = 0;
	}
}

void SpriteAnimado::esVisible(bool visible){
	this->visible = visible;
}

void SpriteAnimado::pararAnimacion(){
	/*this->_frameIndex = 0;
	this->animacionFinalizada(this->_animacionActual);*/
}

void SpriteAnimado::update(int largo){
	if (this->frameIndex<largo){
		this->frameIndex=this->frameIndex+1;
	}
	else{
		this->frameIndex=0;
	}


	/*Sprite::update();

	this->tiempoTrancurrido += elapsedTime;
	if(this->tiempoTrancurrido > this->_timeToUpdate){
		this->tiempoTrancurrido -=this->_timeToUpdate;
		if(this->_frameIndex < this->_animaciones[this->_animacionActual].size() - 1){
			this-> _frameIndex++;
		}
		else{
			if(this->_animacionActualUnica == true){
				this->esVisible(false);
			}
			this->_frameIndex = 0;
			this->animacionFinalizada(this->_animacionActual);
		}
	}*/
}

void SpriteAnimado::dibujar(ControladorGrafico &graficos, int x, int y){
	if(this->visible){
		SDL_Rect rectanguloDestino;
		rectanguloDestino.x = x ;
		rectanguloDestino.y = y ;
		rectanguloDestino.w = this->ancho ;
		rectanguloDestino.h = this->alto ;

		SDL_Rect sourceRect = this->animacion[this->animacionActual][this->frameIndex];
		graficos.dibujarImagen(this->spriteSheet, &sourceRect, &rectanguloDestino);
	}
}

void SpriteAnimado::animacionFinalizada(string currentAnimation){

}



