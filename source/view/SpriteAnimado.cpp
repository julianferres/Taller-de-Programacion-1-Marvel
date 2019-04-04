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
string SpriteAnimado::getAnimacionActual(){
	return this->animacionActual;
}
void SpriteAnimado::cargarAnimaciones(string nombre){
	if(nombre=="CapitanAmerica" or nombre=="CapitanAmerica2"){
		this->agregarAnimacion(6,0,158,"movDerecha",100,122);
		this->agregarAnimacion(9,0,16,"quieto",100,120);
		this->agregarAnimacion(3,0,740,"agacharse",100,105);
		this->agregarAnimacion(6,0,288,"movIzquierda",100,122);
		this->agregarAnimacion(6,0,422,"salto",100,171);
	}
	if((nombre=="Spiderman") or (nombre=="Spiderman2")){
		this->agregarAnimacion(6,0,158,"movDerecha",100,122);
		this->agregarAnimacion(9,0,16,"quieto",100,120);
		this->agregarAnimacion(3,0,740,"agacharse",100,105);
		this->agregarAnimacion(6,0,288,"movIzquierda",100,122);
		this->agregarAnimacion(6,0,422,"salto",100,171);
	}

}

void SpriteAnimado::agregarAnimacion(int frames, int x, int y, string nombre, int ancho, int alto){
	vector<SDL_Rect> rectangulos;
	for (int i = 0; i < frames; i++){
		SDL_Rect newRect = { x+(i*ancho), y, ancho, alto};
		rectangulos.push_back(newRect);
	}
	this->animacion.insert(pair<string, vector<SDL_Rect> > (nombre, rectangulos));

}

void SpriteAnimado::iniciarAnimacion(string animacion){
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

void SpriteAnimado::update(int salto){
	if (this->frameIndex<this->animacion[this->animacionActual].size() - 1){
		this->frameIndex=this->frameIndex+1;
	}
	else{
		this->frameIndex=0;
		this->animacionFinalizada();
	}
}
void SpriteAnimado::dibujar(ControladorGrafico &graficos, int x, int y){
	if(this->visible){
		SDL_Rect sourceRect = this->animacion[this->animacionActual][this->frameIndex];
		SDL_Rect rectanguloDestino={x, y, sourceRect.w, sourceRect.h};
		graficos.dibujarImagen(this->spriteSheet, &sourceRect, &rectanguloDestino);
	}
}

void SpriteAnimado::animacionFinalizada(){
	this->animacionActual="quieto";
}
