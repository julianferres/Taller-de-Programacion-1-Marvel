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
	if(nombre=="CapitanAmerica" or nombre=="CapitanAmerica2"){
		Animacion *quieto = new Animacion("quieto",9,0,16,100,120,5);
		Animacion *moverDerecha = new Animacion("movDerecha",6,0,158,100,122,3);
		Animacion *moverIzquierda = new Animacion("movIzquierda",6,0,288,100,122,3);
		Animacion *salto = new Animacion("salto",6,0,422,100,171,10);
		Animacion *agacharse = new Animacion("agacharse",3,0,740,100,105,4);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animacionActual = quieto;
	}
	if((nombre=="Spiderman") or (nombre=="Spiderman2")){
		Animacion *quieto = new Animacion("quieto",10,0,0,125,115,5);
		Animacion *moverDerecha = new Animacion("movDerecha",12,0,120,100,98,1);
		Animacion *moverIzquierda = new Animacion("movIzquierda",12,0,120,100,98,1);
		Animacion *salto = new Animacion("salto",6,0,422,100,171,8);
		Animacion *agacharse = new Animacion("agacharse",3,0,740,100,15,2);
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

void SpriteAnimado::dibujar(ControladorGrafico &graficos, int x, int y,int alto, int ancho){
	 if(this->visible){
		SDL_Rect sourceRect = animacionActual->getRectOrigen(this->frameIndex);
		SDL_Rect rectanguloDestino={x, y, ancho,alto};
		graficos.dibujarImagen(this->spriteSheet, &sourceRect, &rectanguloDestino);
	}
}

void SpriteAnimado::animacionFinalizada(){
	this->cambiarAnimacion("quieto");
}
