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

int SpriteAnimado::getAlto(){
	return this->animacionActual->getAlto();
}

int SpriteAnimado::getAncho(){
	return this->animacionActual->getAncho();
}

void SpriteAnimado::cargarAnimaciones(string nombre){
	if(nombre == "CapitanAmerica" ){
		quieto = new Animacion("quieto",9,11,16,100,120,6);
		moverDerecha = new Animacion("movDerecha",6,0,158,100,122,4);
		moverIzquierda = new Animacion("movIzquierda",6,0,288,100,122,4);
		salto = new Animacion("salto",9,0,590,125,160,6);
		agacharse = new Animacion("agacharse",3,0,748,100,93,4);
		cambioEntrada = new Animacion("cambioEntrada",7,125,420,125,158,2);
		golpeS=new Animacion("golpeS",3,0,872,140,114,10);//golpe simple LISTO
		patadaS=new Animacion("patadaS",3,0,2079,123,120,6);//patada simple LISTO
		golpeF=new Animacion("golpeF",7,0,1042,231,125,3);//golpe fuerte LISTO
		patadaF=new Animacion("patadaF",4,400,2077,130,130,6);//patada fuerte LISTO
		golpeA=new Animacion("golpeA",4,470,860,125,150,6);//golpe agachado fuerte LISTO
		patadaA=new Animacion("patadaA",4,0,3993,120,82,4);//patada agachado LISTO
		golpeSaltando=new Animacion("golpeSaltando",5,310,2943,155,163,5);//golpe saltando LISTO
		patadaSaltando=new Animacion("patadaSaltando",7,0,3513,172,163,5);//patada saltando LISTO
		defensa=new Animacion("defensa",2,385,742,103,110,7); //LISTO
		disparo=new Animacion("disparar",7,0,1539,275,115,4); //LISTO
		Animacion *atraparEscudo = new Animacion("atraparEscudo",6,435,1668,145,124,6);//LISTO
		animaciones.push_back(atraparEscudo);
		tiro=new Animacion("tirar",8,0,3268,225,172,8);
		rgolpe=new Animacion("recibirGolpe",3,0,4128,225,172,8);
		boton = false;
	}
	else if(nombre=="Spiderman"){
		quieto = new Animacion("quieto",10,1365,7,105,85,5);
		moverDerecha = new Animacion("movDerecha",12,0,120,100,99,2);
		moverIzquierda = new Animacion("movIzquierda",12,0,120,100,99,2);
		salto = new Animacion("salto",14,0,473,100,135,3);
		agacharse = new Animacion("agacharse",13,0,1205,110,65,4);
		cambioEntrada = new Animacion("cambioEntrada",14,0,227,110,133,2);
		golpeS=new Animacion("golpeS",5,0,633,158,85,4);//golpe simple LISTO
		patadaS=new Animacion("patadaS",4,1270,930,153,102,4);//patada simple LISTO
		golpeSaltando=new Animacion("golpeSaltando",10,0,766,138,120,4);//golpe saltando LISTO
		patadaSaltando=new Animacion("patadaSaltando",10,0,1900,152,125,4);//patada saltando LISTO
		golpeF=new Animacion("golpeF",8,900,608,151,145,4);//golpe fuerte LISTO
		patadaF=new Animacion("patadaF",6,150,916,145,125,4);//patada fuerte LISTO
		golpeA=new Animacion("golpeA",8,790,2748,155,150,5);//golpe agachado LISTO
		patadaA=new Animacion("patadaA",5,1030,1405,140,70,5);//patada agachado LISTO
		defensa=new Animacion("defensa",4,0,2377,110,110,6); //LISTO
		disparo=new Animacion("disparar",7,0,2500,275,84,3); //LISTO
		tiro=new Animacion("tirar",6,0,3440,225,172,8);
		rgolpe=new Animacion("recibirGolpe",3,0,4128,225,172,8);
		boton = false;
	}
	else if(nombre=="Venom" ){
		quieto = new Animacion("quieto",13,0,0,225,172,5);
		moverDerecha = new Animacion("movDerecha",10,0,344,225,172,4);
		moverIzquierda = new Animacion("movIzquierda",10,0,344,225,172,4);
		salto = new Animacion("salto",11,0,688,225,172,6);
		agacharse = new Animacion("agacharse",10,0,516,225,172,2);
		cambioEntrada = new Animacion("cambioEntrada",11,0,860,225,172,2);
		golpeS=new Animacion("golpeS",3,0,172,225,172,8);//golpe simple
		patadaS=new Animacion("patadaS",3,0,1376,225,172,8);//patada simple
		golpeSaltando=new Animacion("golpeSaltando",9,0,1204,225,172,6);//golpe saltando
		patadaSaltando=new Animacion("patadaSaltando",9,0,1720,225,172,6);//patada saltando
		golpeF=new Animacion("golpeF",7,0,1892,225,172,8);//golpe fuerte
		patadaF=new Animacion("patadaF",9,0,2064,225,172,6);//patada fuerte
		golpeA=new Animacion("golpeA",7,0,2236,225,172,8);//golpe agachado
		patadaA=new Animacion("patadaA",5,0,2408,225,172,16);//patada agachado
		defensa=new Animacion("defensa",10,0,2924,225,172,8);
		disparo=new Animacion("disparar",8,0,3268,225,172,8);
		tiro=new Animacion("tirar",6,0,3440,225,172,8);
		rgolpe=new Animacion("recibirGolpe",3,0,4128,225,172,8);
		boton = false;
	}
	else if(nombre=="MegaMan" ){
		quieto = new Animacion("quieto",6,0,0,225,172,10);
		moverDerecha = new Animacion("movDerecha",12,0,172,225,172,4);
		moverIzquierda = new Animacion("movIzquierda",12,0,344,225,172,4);
		salto = new Animacion("salto",13,0,516,225,172,4);
		agacharse = new Animacion("agacharse",10,0,688,225,172,2);
		cambioEntrada = new Animacion("cambioEntrada",12,0,1892,225,172,2);
		golpeS=new Animacion("golpeS",4,0,860,225,172,6);//golpe simple
		patadaS=new Animacion("patadaS",4,0,1032,225,172,8);//patada simple
		golpeSaltando=new Animacion("golpeSaltando",3,0,1548,225,172,8);//golpe saltando
		patadaSaltando=new Animacion("patadaSaltando",4,0,1720,225,172,8);//patada saltando
		golpeF=new Animacion("golpeF",8,0,2236,225,172,8);//golpe fuerte
		patadaF=new Animacion("patadaF",8,0,2408,225,172,6);//patada fuerte
		golpeA=new Animacion("golpeA",8,0,2580,225,172,8);//golpe agachado
		patadaA=new Animacion("patadaA",7,0,2752,225,172,8);//patada agachado
		defensa=new Animacion("defensa",4,0,2064,225,172,8);
		disparo=new Animacion("disparar",8,0,3268,225,172,8);
		tiro=new Animacion("tirar",6,0,3440,225,172,8);
		rgolpe=new Animacion("recibirGolpe",3,0,4128,225,172,8);
		boton = false;
	}
	else if(nombre=="Hulk" ){
		quieto = new Animacion("quieto",8,0,0,170,130,10);
		moverDerecha = new Animacion("movDerecha",16,0,130,170,150,4);
		moverIzquierda = new Animacion("movIzquierda",16,0,285,170,150,4);
		salto = new Animacion("salto",10,0,580,170,215,6);
		agacharse = new Animacion("agacharse",5,0,450,170,123,4);
		cambioEntrada = new Animacion("cambioEntrada",8,0,1119,170,248,3);
		golpeS=new Animacion("golpeS",5,0,450,170,123,4);//golpe simple
		patadaS=new Animacion("patadaS",5,0,450,170,123,4);//patada simple
		golpeSaltando=new Animacion("golpeSaltando",5,0,450,170,123,4);//golpe saltando
		patadaSaltando=new Animacion("patadaSS",5,0,450,170,123,4);//patada saltando
		golpeF=new Animacion("golpeF",3,0,1032,225,172,8);//golpe fuerte
		patadaF=new Animacion("patadaF",6,0,1204,225,172,6);//patada fuerte
		golpeA=new Animacion("golpeA",3,0,1548,225,172,8);//golpe agachado
		patadaA=new Animacion("patadaA",4,0,1376,225,172,16);//patada agachado
		defensa=new Animacion("defensa",1,1,1,1,1,1);
		disparo=new Animacion("disparar",8,0,3268,225,172,8);
		tiro=new Animacion("tirar",6,0,3440,225,172,8);
		rgolpe=new Animacion("recibirGolpe",3,0,4128,225,172,8);
		boton = false;
	}
	else if(nombre=="SinSprite" ){
		quieto = new Animacion("quieto",1,0,0,600,600,10);
		moverDerecha = new Animacion("movDerecha",1,0,0,600,600,4);
		moverIzquierda = new Animacion("movIzquierda",1,0,0,600,600,4);
		//cambioSalida = new Animacion("cambioSalida",1,0,0,600,600,4);
		cambioEntrada = new Animacion("cambioEntrada",1,0,0,600,600,4);
		salto = new Animacion("salto",1,0,0,600,600,10);
		agacharse = new Animacion("agacharse",1,0,0,600,600,2);
		golpeS=new Animacion("golpeS",1,0,0,600,600,2);//golpe simple
		patadaS=new Animacion("patadaS",1,0,0,600,600,2);//patada simple
		golpeSaltando=new Animacion("golpeSaltando",1,0,0,600,600,2);//golpe saltando
		patadaSaltando=new Animacion("patadaSS",1,0,0,600,600,2);//patada saltando
		golpeF=new Animacion("golpeF",1,0,0,600,600,10);//golpe fuerte
		patadaF=new Animacion("patadaF",1,0,0,600,600,10);//patada fuerte
		golpeA=new Animacion("golpeA",1,0,0,600,600,10);//golpe agachado
		patadaA=new Animacion("patadaA",1,0,0,600,600,10);//patada agachado
		defensa=new Animacion("defensa",1,0,0,600,600,10);
		disparo=new Animacion("disparar",1,0,0,600,600,10);
		tiro=new Animacion("tirar",1,0,0,600,600,10);
		rgolpe=new Animacion("recibirGolpe",1,0,0,600,600,10);
		boton = false;
	}
	if(!boton){
		animaciones.push_back(disparo);
		animaciones.push_back(tiro);
		animaciones.push_back(rgolpe);
		animaciones.push_back(defensa);

		animaciones.push_back(golpeS);
		animaciones.push_back(golpeF);
		animaciones.push_back(golpeA);
		animaciones.push_back(golpeSaltando);

		animaciones.push_back(patadaS);
		animaciones.push_back(patadaF);
		animaciones.push_back(patadaA);
		animaciones.push_back(patadaSaltando);

		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animaciones.push_back(cambioEntrada);
		animacionActual = quieto;
		return;
	}

	//std::string Nombre, int Frames,int x,int y, int ancho, int alto,int Velocidad
	if(nombre=="CapitanAmericaBoton"){
		mouseOut = new Animacion("mouseOut",1,0,0,159,129,10);
		mouseOver = new Animacion("mouseOver",1,160,0,159,129,10);
		mouseDown = new Animacion("mouseDown",1,319,0,159,129,10);
		mouseUp = new Animacion("mouseUp",1,478,0,159,129,10);
	}
	else if(nombre=="SpidermanBoton"){
		mouseOut = new Animacion("mouseOut",1,0,0,170,138,10);
		mouseOver = new Animacion("mouseOver",1,171,0,170,138,10);
		mouseDown = new Animacion("mouseDown",1,342,0,170,138,10);
		mouseUp = new Animacion("mouseUp",1,513,0,170,138,10);
	}
	else if(nombre=="HulkBoton"){
		mouseOut = new Animacion("mouseOut",1,0,0,164,129,10);
		mouseOver = new Animacion("mouseOver",1,165,0,164,129,10);
		mouseDown = new Animacion("mouseDown",1,330,0,164,129,10);
		mouseUp = new Animacion("mouseUp",1,495,0,164,129,10);

	}
	else if(nombre=="MegaManBoton"){
		mouseOut = new Animacion("mouseOut",1,0,0,164,129,10);
		mouseOver = new Animacion("mouseOver",1,165,0,164,129,10);
		mouseDown = new Animacion("mouseDown",1,330,0,164,129,10);
		mouseUp = new Animacion("mouseUp",1,495,0,164,129,10);
	}
	else if(nombre=="VenomBoton"){
		mouseOut = new Animacion("mouseOut",1,0,0,175,145,10);
		mouseOver = new Animacion("mouseOver",1,176,0,175,145,10);
		mouseDown = new Animacion("mouseDown",1,352,0,175,145,10);
		mouseUp = new Animacion("mouseUp",1,528,0,175,145,10);
	}
	else if(nombre=="SinSpriteBoton"){
		mouseOut = new Animacion("mouseOut",1,0,0,71,61,10);
		mouseOver = new Animacion("mouseOver",1,72,0,71,61,10);
		mouseDown = new Animacion("mouseDown",1,144,0,71,61,10);
		mouseUp = new Animacion("mouseUp",1,216,0,71,61,10);
	}else {
		mouseOut = new Animacion("mouseOut",1,0,0,175,145,10);
		mouseOver = new Animacion("mouseOver",1,175,0,175,145,10);
		mouseDown = new Animacion("mouseDown",1,350,0,175,145,10);
		mouseUp = new Animacion("mouseUp",1,525,0,175,145,10);
	}
	animaciones.push_back(mouseOut);
	animaciones.push_back(mouseOver);
	animaciones.push_back(mouseDown);
	animaciones.push_back(mouseUp);
	animacionActual = mouseOut;
}

bool SpriteAnimado::iniciarAnimacion(string nombre){
	if(animacionActual->getNombre()=="cambioEntrada" || animacionActual->getNombre()=="disparar" ) return false;
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
		if(animacionActual->getNombre()=="agacharse" || animacionActual->getNombre()=="defensa")
			return;
		frameIndex=0;
		if(nombreSprite == "CapitanAmerica" && animacionActual->getNombre()=="disparar")
			cambiarAnimacion("atraparEscudo");

		else if(animacionActual->getNombre()!="movDerecha" && animacionActual->getNombre()!="movIzquierda")
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
