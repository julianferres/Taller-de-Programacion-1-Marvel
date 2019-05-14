#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>
#include <Animacion.hpp>
#include <ControladorLogger.hpp>
#include <ControladorJson.hpp>

using namespace std;

SpriteAnimado::~SpriteAnimado(){

	for(Uint16 i = 0; i<animaciones.size();i++)
		if(animaciones[i]) delete animaciones[i];

	animaciones.clear();
	SDL_FreeSurface(surface);
}

SpriteAnimado::SpriteAnimado(string nombre){
	//surface = graficos.cargarImagen(filePath);
	//this->spriteSheet = SDL_CreateTextureFromSurface(graficos.getRenderer(),surface);
	this->nombreSprite = nombre;
	cargarAnimaciones(nombre);
}

string SpriteAnimado::getAnimacionActual(){
	return this->animacionActual->getNombre();
}

string SpriteAnimado::getNombre(){
	return this->nombreSprite;
}

void SpriteAnimado::cargarAnimaciones(string nombre){
	if(nombre == "CapitanAmerica" ){
		Animacion *quieto = new Animacion("quieto",9,0,16,100,120,6);
		Animacion *moverDerecha = new Animacion("movDerecha",6,0,158,100,122,4);
		Animacion *moverIzquierda = new Animacion("movIzquierda",6,0,288,100,122,4);
		Animacion *salto = new Animacion("salto",8,0,595,125,135,10);
		Animacion *agacharse = new Animacion("agacharse",3,0,740,100,105,4);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",8,0,420,125,158,2);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animaciones.push_back(cambioEntrada);
		animacionActual = quieto;
	}
	else if(nombre=="Spiderman"){
		Animacion *quieto = new Animacion("quieto",10,0,0,125,115,5);
		Animacion *moverDerecha = new Animacion("movDerecha",12,0,120,100,99,2);
		Animacion *moverIzquierda = new Animacion("movIzquierda",12,0,120,100,99,2);
		Animacion *salto = new Animacion("salto",14,0,473,100,135,2);
		Animacion *agacharse = new Animacion("agacharse",13,0,1180,110,90,4);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",14,0,227,110,133,2);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animaciones.push_back(cambioEntrada);
		animacionActual = quieto;
		return;
	}
	else if(nombre=="Venom" ){
		Animacion *quieto = new Animacion("quieto",13,0,519,160,123,5);
		Animacion *moverDerecha = new Animacion("movDerecha",10,0,2905,160,130,4);
		Animacion *moverIzquierda = new Animacion("movIzquierda",10,0,2905,160,130,4);
		Animacion *salto = new Animacion("salto",11,0,5408,160,172,8);
		Animacion *agacharse = new Animacion("agacharse",10,0,3580,150,125,2);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",11,0,5668,160,162,2);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animaciones.push_back(cambioEntrada);
		animacionActual = quieto;
		return;
	}
	else if(nombre=="MegaMan" ){
		Animacion *quieto = new Animacion("quieto",6,0,0,80,70,15);
		Animacion *moverDerecha = new Animacion("movDerecha",12,0,108,100,82,4);
		Animacion *moverIzquierda = new Animacion("movIzquierda",12,0,108,100,82,4);
		Animacion *salto = new Animacion("salto",13,0,1572,100,152,10);
		Animacion *agacharse = new Animacion("agacharse",10,0,965,100,80,2);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",13,0,1572,100,152,10);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animaciones.push_back(cambioEntrada);
		animacionActual = quieto;

	}
	else if(nombre=="Hulk" ){
		Animacion *quieto = new Animacion("quieto",8,0,0,170,125,10);
		Animacion *moverDerecha = new Animacion("movDerecha",16,0,280,170,150,4);
		Animacion *moverIzquierda = new Animacion("movIzquierda",16,0,130,170,143,4);
		Animacion *salto = new Animacion("salto",10,0,580,170,215,8);
		Animacion *agacharse = new Animacion("agacharse",5,0,445,170,123,4);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",8,0,1112,170,248,3);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animaciones.push_back(cambioEntrada);
		animacionActual = quieto;
	}
	else if(nombre=="sinSprite" ){
		Animacion *quieto = new Animacion("quieto",1,0,0,600,600,10);
		Animacion *moverDerecha = new Animacion("movDerecha",1,0,0,600,600,4);
		Animacion *moverIzquierda = new Animacion("movIzquierda",1,0,0,600,600,4);
		Animacion *cambioSalida = new Animacion("cambioSalida",1,0,0,600,600,4);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",1,0,0,600,600,4);
		Animacion *salto = new Animacion("salto",1,0,0,600,600,10);
		Animacion *agacharse = new Animacion("agacharse",1,0,0,600,600,2);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animaciones.push_back(cambioSalida);
		animaciones.push_back(cambioEntrada);
		animacionActual = quieto;
	}
	//std::string Nombre, int Frames,int x,int y, int ancho, int alto,int Velocidad
	else if(nombre=="CapitanAmericaBoton"){
		Animacion *mouseOut = new Animacion("mouseOut",1,0,0,159,129,10);
		Animacion *mouseOver = new Animacion("mouseOver",1,159,0,159,129,10);
		Animacion *mouseDown = new Animacion("mouseDown",1,318,0,159,129,10);
		Animacion *mouseUp = new Animacion("mouseUp",1,477,0,159,129,10);
		animaciones.push_back(mouseOut);
		animaciones.push_back(mouseOver);
		animaciones.push_back(mouseDown);
		animaciones.push_back(mouseUp);
		animacionActual = mouseOut;
	}
	else if(nombre=="SpidermanBoton"){
		Animacion *mouseOut = new Animacion("mouseOut",1,0,0,170,138,10);
		Animacion *mouseOver = new Animacion("mouseOver",1,170,0,170,138,10);
		Animacion *mouseDown = new Animacion("mouseDown",1,340,0,170,138,10);
		Animacion *mouseUp = new Animacion("mouseUp",1,510,0,170,138,10);
		animaciones.push_back(mouseOut);
		animaciones.push_back(mouseOver);
		animaciones.push_back(mouseDown);
		animaciones.push_back(mouseUp);
		animacionActual = mouseOut;
	}
	else if(nombre=="HulkBoton"){
		Animacion *mouseOut = new Animacion("mouseOut",1,0,0,164,129,10);
		Animacion *mouseOver = new Animacion("mouseOver",1,164,0,164,129,10);
		Animacion *mouseDown = new Animacion("mouseDown",1,328,0,164,129,10);
		Animacion *mouseUp = new Animacion("mouseUp",1,492,0,164,129,10);
		animaciones.push_back(mouseOut);
		animaciones.push_back(mouseOver);
		animaciones.push_back(mouseDown);
		animaciones.push_back(mouseUp);
		animacionActual = mouseOut;
	}
	else if(nombre=="VenomBoton"){
		Animacion *mouseOut = new Animacion("mouseOut",1,0,0,175,145,10);
		Animacion *mouseOver = new Animacion("mouseOver",1,175,0,175,145,10);
		Animacion *mouseDown = new Animacion("mouseDown",1,350,0,175,145,10);
		Animacion *mouseUp = new Animacion("mouseUp",1,525,0,175,145,10);
		animaciones.push_back(mouseOut);
		animaciones.push_back(mouseOver);
		animaciones.push_back(mouseDown);
		animaciones.push_back(mouseUp);
		animacionActual = mouseOut;
	}
	else {
		Animacion *mouseOut = new Animacion("mouseOut",1,0,0,175,145,10);
		Animacion *mouseOver = new Animacion("mouseOver",1,175,0,175,145,10);
		Animacion *mouseDown = new Animacion("mouseDown",1,350,0,175,145,10);
		Animacion *mouseUp = new Animacion("mouseUp",1,525,0,175,145,10);
		animaciones.push_back(mouseOut);
		animaciones.push_back(mouseOver);
		animaciones.push_back(mouseDown);
		animaciones.push_back(mouseUp);
		animacionActual = mouseOut;
	}
}

bool SpriteAnimado::iniciarAnimacion(string nombre){
	if(animacionActual->getNombre().compare("cambioEntrada") == 0) return false;
	if( animacionActual->getNombre() != nombre){
		cambiarAnimacion(nombre);
		frameIndex = 0;
	}
	return true;
}

void SpriteAnimado::cambiarAnimacion(string nombre){
	for(Uint8 i=0; i<animaciones.size();i++){
		if(animaciones[i]->getNombre() == nombre )
			animacionActual = animaciones[i];
	}
}

void SpriteAnimado::pararAnimacion(){
	this->frameIndex = 0;
	this->cambiarAnimacion("quieto");
}

void SpriteAnimado::update(){
	if( regulador < animacionActual->getVelocidad()){
		regulador++;
		return;
	}
	if (frameIndex < animacionActual->getFrames() - 1 )
		frameIndex++;
	else{
		if(animacionActual->getNombre()=="agacharse"){
			return;
		}

		this->frameIndex=0;
		this->animacionFinalizada();
	}
	regulador = 0;
}

int SpriteAnimado::getFrameIndex(){
	return this->frameIndex;
}

SDL_Rect SpriteAnimado::rectOrigen(){
	return animacionActual->getRectOrigen(this->frameIndex);
}


void SpriteAnimado::dibujar(ControladorGrafico &graficos, int x, int y,int alto, int ancho, SDL_RendererFlip flip){

	SDL_Rect sourceRect = animacionActual->getRectOrigen(this->frameIndex);
	SDL_Rect rectanguloDestino={x, y, ancho,alto};
	graficos.dibujarImagen(this->spriteSheet, &sourceRect, &rectanguloDestino, flip);

}

void SpriteAnimado::animacionFinalizada(){
	this->cambiarAnimacion("quieto");
}
