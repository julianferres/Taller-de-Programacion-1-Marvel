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
}

SpriteAnimado::SpriteAnimado(string nombre){
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
		Animacion *quieto = new Animacion("quieto",9,11,16,100,120,6);
		Animacion *moverDerecha = new Animacion("movDerecha",6,0,158,100,122,4);
		Animacion *moverIzquierda = new Animacion("movIzquierda",6,0,288,100,122,4);
		Animacion *salto = new Animacion("salto",8,0,590,125,140,7);
		Animacion *agacharse = new Animacion("agacharse",3,0,740,100,105,4);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",7,125,420,125,158,2);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animaciones.push_back(cambioEntrada);
		animacionActual = quieto;
	}
	else if(nombre=="Spiderman"){
		Animacion *quieto = new Animacion("quieto",10,1365,7,105,85,5);
		Animacion *moverDerecha = new Animacion("movDerecha",12,0,120,100,99,2);
		Animacion *moverIzquierda = new Animacion("movIzquierda",12,0,120,100,99,2);
		Animacion *salto = new Animacion("salto",14,0,473,100,135,3);
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
		Animacion *salto = new Animacion("salto",11,0,5408,160,172,6);
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
		Animacion *quieto = new Animacion("quieto",8,0,0,170,130,10);
		Animacion *moverDerecha = new Animacion("movDerecha",16,0,130,170,150,4);
		Animacion *moverIzquierda = new Animacion("movIzquierda",16,0,130,170,150,4);
		Animacion *salto = new Animacion("salto",10,0,580,170,215,6);
		Animacion *agacharse = new Animacion("agacharse",5,0,450,170,123,4);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",8,0,1119,170,248,3);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animaciones.push_back(cambioEntrada);
		animacionActual = quieto;
	}
	else if(nombre=="SinSprite" ){
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
		Animacion *mouseOver = new Animacion("mouseOver",1,160,0,159,129,10);
		Animacion *mouseDown = new Animacion("mouseDown",1,319,0,159,129,10);
		Animacion *mouseUp = new Animacion("mouseUp",1,478,0,159,129,10);
		animaciones.push_back(mouseOut);
		animaciones.push_back(mouseOver);
		animaciones.push_back(mouseDown);
		animaciones.push_back(mouseUp);
		animacionActual = mouseOut;
	}
	else if(nombre=="SpidermanBoton"){
		Animacion *mouseOut = new Animacion("mouseOut",1,0,0,170,138,10);
		Animacion *mouseOver = new Animacion("mouseOver",1,171,0,170,138,10);
		Animacion *mouseDown = new Animacion("mouseDown",1,342,0,170,138,10);
		Animacion *mouseUp = new Animacion("mouseUp",1,513,0,170,138,10);
		animaciones.push_back(mouseOut);
		animaciones.push_back(mouseOver);
		animaciones.push_back(mouseDown);
		animaciones.push_back(mouseUp);
		animacionActual = mouseOut;
	}
	else if(nombre=="HulkBoton"){
		Animacion *mouseOut = new Animacion("mouseOut",1,0,0,164,129,10);
		Animacion *mouseOver = new Animacion("mouseOver",1,165,0,164,129,10);
		Animacion *mouseDown = new Animacion("mouseDown",1,330,0,164,129,10);
		Animacion *mouseUp = new Animacion("mouseUp",1,495,0,164,129,10);
		animaciones.push_back(mouseOut);
		animaciones.push_back(mouseOver);
		animaciones.push_back(mouseDown);
		animaciones.push_back(mouseUp);
		animacionActual = mouseOut;
	}
	else if(nombre=="VenomBoton"){
		Animacion *mouseOut = new Animacion("mouseOut",1,0,0,175,145,10);
		Animacion *mouseOver = new Animacion("mouseOver",1,176,0,175,145,10);
		Animacion *mouseDown = new Animacion("mouseDown",1,352,0,175,145,10);
		Animacion *mouseUp = new Animacion("mouseUp",1,528,0,175,145,10);
		animaciones.push_back(mouseOut);
		animaciones.push_back(mouseOver);
		animaciones.push_back(mouseDown);
		animaciones.push_back(mouseUp);
		animacionActual = mouseOut;
	}
	else if(nombre=="SinSpriteBoton"){
		Animacion *mouseOut = new Animacion("mouseOut",1,0,0,71,61,10);
		Animacion *mouseOver = new Animacion("mouseOver",1,72,0,71,61,10);
		Animacion *mouseDown = new Animacion("mouseDown",1,144,0,71,61,10);
		Animacion *mouseUp = new Animacion("mouseUp",1,216,0,71,61,10);
		animaciones.push_back(mouseOut);
		animaciones.push_back(mouseOver);
		animaciones.push_back(mouseDown);
		animaciones.push_back(mouseUp);
		animacionActual = mouseOut;
	}else {
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
	if( animacionActual->getNombre() != nombre || nombre=="quieto")
		cambiarAnimacion(nombre);

	return true;
}

void SpriteAnimado::cambiarAnimacion(string nombre){
	for(Uint8 i=0; i<animaciones.size();i++){
		if(animaciones[i]->getNombre() == nombre )
			animacionActual = animaciones[i];
	}
	frameIndex = 0;
}

void SpriteAnimado::update(){
	if( regulador < animacionActual->getVelocidad()){
		regulador++;
		return;
	}
	if (frameIndex < animacionActual->getFrames() - 1 )
		frameIndex++;
	else{
		if(animacionActual->getNombre()=="agacharse")
			return;
		frameIndex=0;
		if(animacionActual->getNombre()!="movDerecha" && animacionActual->getNombre()!="movIzquierda")
			cambiarAnimacion("quieto");
	}
	regulador = 0;
}

int SpriteAnimado::getFrameIndex(){
	return this->frameIndex;
}

SDL_Rect SpriteAnimado::rectOrigen(){
	return animacionActual->getRectOrigen(this->frameIndex);
}
