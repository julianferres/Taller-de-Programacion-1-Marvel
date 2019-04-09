#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>
#include <Animacion.hpp>

class Animacion;
using namespace std;

SpriteAnimado::SpriteAnimado(){
}

SpriteAnimado::SpriteAnimado(ControladorGrafico &graficos, const string &filePath){
	this->spriteSheet = SDL_CreateTextureFromSurface(graficos.getRenderer(),graficos.cargarImagen(filePath));
}

string SpriteAnimado::getAnimacionActual(){
	return this->animacionActual->getNombre();
}

void SpriteAnimado::cargarAnimaciones(string nombre){
	if(nombre == "CapitanAmerica" ){
		Animacion *quieto = new Animacion("quieto",9,0,16,100,120,4);
		Animacion *moverDerecha = new Animacion("movDerecha",6,0,158,100,122,5);
		Animacion *moverIzquierda = new Animacion("movIzquierda",6,0,288,100,122,5);
		Animacion *salto = new Animacion("salto",8,0,595,125,135,9);
		Animacion *agacharse = new Animacion("agacharse",3,0,740,100,105,4);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animacionActual = quieto;
	}
	else if(nombre=="Spiderman"){
		Animacion *quieto = new Animacion("quieto",10,0,0,125,115,5);
		Animacion *moverDerecha = new Animacion("movDerecha",12,0,120,100,99,1);
		Animacion *moverIzquierda = new Animacion("movIzquierda",12,0,120,100,99,1);
		Animacion *salto = new Animacion("salto",14,0,473,100,135,2);
		Animacion *agacharse = new Animacion("agacharse",13,0,1208,110,66,8);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animacionActual = quieto;
	}
	else if(nombre=="Venom" ){
			Animacion *quieto = new Animacion("quieto",13,0,519,160,123,5);
			Animacion *moverDerecha = new Animacion("movDerecha",10,0,2905,160,130,4);
			Animacion *moverIzquierda = new Animacion("movIzquierda",10,0,2905,160,130,4);
			Animacion *salto = new Animacion("salto",11,0,5408,160,172,8);
			Animacion *agacharse = new Animacion("agacharse",10,0,3580,150,125,2);
			animaciones.push_back(quieto);
			animaciones.push_back(moverDerecha);
			animaciones.push_back(moverIzquierda);
			animaciones.push_back(salto);
			animaciones.push_back(agacharse);
			animacionActual = quieto;
		}
	else if(nombre=="MegaMan" ){
				Animacion *quieto = new Animacion("quieto",6,0,0,100,80,5);
				Animacion *moverDerecha = new Animacion("movDerecha",12,0,108,100,82,4);
				Animacion *moverIzquierda = new Animacion("movIzquierda",12,0,108,100,82,4);
				Animacion *salto = new Animacion("salto",13,0,1572,100,152,8);
				Animacion *agacharse = new Animacion("agacharse",10,0,965,100,80,2);
				animaciones.push_back(quieto);
				animaciones.push_back(moverDerecha);
				animaciones.push_back(moverIzquierda);
				animaciones.push_back(salto);
				animaciones.push_back(agacharse);
				animacionActual = quieto;
			}
}

void SpriteAnimado::iniciarAnimacion(string nombre){
	if( animacionActual->getNombre() != nombre){
		cambiarAnimacion(nombre);
		frameIndex = 0;
	}
}

void SpriteAnimado::cambiarAnimacion(string nombre){
	for(Uint8 i=0; i<animaciones.size();i++){
		if(animaciones[i]->getNombre() == nombre )
			animacionActual = animaciones[i];
	}
}

void SpriteAnimado::esVisible(bool visible){
	this->visible = visible;
}

void SpriteAnimado::pararAnimacion(){
	/*this->_frameIndex = 0;
	this->animacionFinalizada(this->_animacionActual);*/
}

void SpriteAnimado::update(){
	if( regulador < animacionActual->getVelocidad()){
		regulador++;
		return;
	}
	if (frameIndex < animacionActual->getFrames() - 1 )
		frameIndex++;
	else{
		this->frameIndex=0;
		this->animacionFinalizada();
	}
	regulador = 0;
}

void SpriteAnimado::dibujar(ControladorGrafico &graficos, int x, int y,int alto, int ancho, SDL_RendererFlip flip){
	 if(this->visible){
		SDL_Rect sourceRect = animacionActual->getRectOrigen(this->frameIndex);
		SDL_Rect rectanguloDestino={x, y, ancho,alto};
		graficos.dibujarImagen(this->spriteSheet, &sourceRect, &rectanguloDestino, flip);
	}
}

void SpriteAnimado::animacionFinalizada(){
	this->cambiarAnimacion("quieto");
}
