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
		Animacion *quieto = new Animacion("quieto",9,0,0,225,172,6);
		Animacion *moverDerecha = new Animacion("movDerecha",6,0,172,225,172,4);
		Animacion *moverIzquierda = new Animacion("movIzquierda",6,0,344,225,172,4);
		Animacion *salto = new Animacion("salto",8,0,688,225,172,7);
		Animacion *agacharse = new Animacion("agacharse",3,0,860,225,172,4);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",7,0,516,225,172,2);
		Animacion *golpeS=new Animacion("golpeS",3,0,1032,225,172,8);//golpe simple
		Animacion *patadaS=new Animacion("patadaS",3,0,1204,225,172,6);//patada simple
		Animacion *golpeAS=new Animacion("golpeAS",3,0,1548,225,172,8);//golpe agachado simple
		Animacion *patadaAS=new Animacion("patadaAS",3,0,1376,225,172,16);//patada agachado simple
		Animacion *golpeSS=new Animacion("golpeSS",4,0,1892,225,172,10);//golpe saltando simple
		Animacion *patadaSS=new Animacion("patadaSS",5,0,1720,225,172,10);//patada saltando simple
		Animacion *golpeF=new Animacion("golpeF",5,0,2064,225,172,8);//golpe fuerte
		Animacion *patadaF=new Animacion("patadaF",6,0,2236,225,172,6);//patada fuerte
		Animacion *golpeAF=new Animacion("golpeAF",4,0,2408,225,172,8);//golpe agachado fuerte
		Animacion *patadaAF=new Animacion("patadaAF",4,0,2580,225,172,16);//patada agachado fuerte
		Animacion *golpeSF=new Animacion("golpeSF",5,0,2752,225,172,10);//golpe saltando fuerte
		Animacion *patadaSF=new Animacion("patadaSF",4,0,2924,225,172,10);//patada saltando fuerte
		Animacion *defensa=new Animacion("defensa",3,0,3096,225,172,10);
		Animacion *disparo=new Animacion("disparar",8,0,3268,225,172,8);
		Animacion *tiro=new Animacion("tirar",6,0,3440,225,172,8);
		Animacion *rgolpe=new Animacion("recibirGolpe",3,0,4128,225,172,8);
		animaciones.push_back(disparo);
		animaciones.push_back(tiro);
		animaciones.push_back(rgolpe);
		animaciones.push_back(defensa);
		animaciones.push_back(golpeF);
		animaciones.push_back(patadaF);
		animaciones.push_back(golpeAF);
		animaciones.push_back(patadaAF);
		animaciones.push_back(golpeSF);
		animaciones.push_back(patadaSF);
		animaciones.push_back(golpeS);
		animaciones.push_back(patadaS);
		animaciones.push_back(golpeAS);
		animaciones.push_back(patadaAS);
		animaciones.push_back(golpeSS);
		animaciones.push_back(patadaSS);
		animaciones.push_back(quieto);
		animaciones.push_back(moverDerecha);
		animaciones.push_back(moverIzquierda);
		animaciones.push_back(salto);
		animaciones.push_back(agacharse);
		animaciones.push_back(cambioEntrada);
		animacionActual = quieto;
	}
	else if(nombre=="Spiderman"){
		Animacion *quieto = new Animacion("quieto",10,0,0,225,172,6);
		Animacion *moverDerecha = new Animacion("movDerecha",12,0,172,225,172,2);
		Animacion *moverIzquierda = new Animacion("movIzquierda",12,0,172,225,172,2);
		Animacion *salto = new Animacion("salto",13,0,344,225,172,3);
		Animacion *agacharse = new Animacion("agacharse",13,0,516,225,172,4);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",14,0,1720,225,172,2);
		Animacion *golpeS=new Animacion("golpeS",5,0,688,225,172,4);//golpe simple
		Animacion *patadaS=new Animacion("patadaS",5,0,860,225,172,4);//patada simple
		Animacion *golpeAS=new Animacion("golpeAS",5,0,1376,225,172,4);//golpe agachado simple
		Animacion *patadaAS=new Animacion("patadaAS",5,0,1548,225,172,4);//patada agachado simple
		Animacion *golpeSS=new Animacion("golpeSS",4,0,1032,225,172,4);//golpe saltando simple
		Animacion *patadaSS=new Animacion("patadaSS",4,0,1204,225,172,4);//patada saltando simple
		Animacion *golpeF=new Animacion("golpeF",7,0,1892,225,172,7);//golpe fuerte
		Animacion *patadaF=new Animacion("patadaF",8,0,2064,225,172,6);//patada fuerte
		Animacion *golpeAF=new Animacion("golpeAF",8,0,2408,225,172,8);//golpe agachado fuerte
		Animacion *patadaAF=new Animacion("patadaAF",6,0,2236,225,172,16);//patada agachado fuerte
		Animacion *golpeSF=new Animacion("golpeSF",7,0,2580,225,172,10);//golpe saltando fuerte
		Animacion *patadaSF=new Animacion("patadaSF",6,0,2752,225,172,10);//patada saltando fuerte
		Animacion *defensa=new Animacion("defensa",10,0,2924,225,172,4);
		Animacion *disparo=new Animacion("disparar",8,0,3268,225,172,8);
		Animacion *tiro=new Animacion("tirar",6,0,3440,225,172,8);
		Animacion *rgolpe=new Animacion("recibirGolpe",3,0,4128,225,172,8);
		animaciones.push_back(disparo);
		animaciones.push_back(tiro);
		animaciones.push_back(rgolpe);
		animaciones.push_back(defensa);	
		animaciones.push_back(golpeF);
		animaciones.push_back(patadaF);
		animaciones.push_back(golpeAF);
		animaciones.push_back(patadaAF);
		animaciones.push_back(golpeSF);
		animaciones.push_back(patadaSF);
		animaciones.push_back(golpeS);
		animaciones.push_back(patadaS);
		animaciones.push_back(golpeAS);
		animaciones.push_back(patadaAS);
		animaciones.push_back(golpeSS);
		animaciones.push_back(patadaSS);
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
		Animacion *quieto = new Animacion("quieto",13,0,0,225,172,5);
		Animacion *moverDerecha = new Animacion("movDerecha",10,0,344,225,172,4);
		Animacion *moverIzquierda = new Animacion("movIzquierda",10,0,344,225,172,4);
		Animacion *salto = new Animacion("salto",11,0,688,225,172,6);
		Animacion *agacharse = new Animacion("agacharse",10,0,516,225,172,2);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",11,0,860,225,172,2);
		Animacion *golpeS=new Animacion("golpeS",3,0,172,225,172,8);//golpe simple
		Animacion *patadaS=new Animacion("patadaS",3,0,1376,225,172,8);//patada simple
		Animacion *golpeAS=new Animacion("golpeAS",3,0,1032,225,172,8);//golpe agachado simple
		Animacion *patadaAS=new Animacion("patadaAS",4,0,1548,225,172,8);//patada agachado simple
		Animacion *golpeSS=new Animacion("golpeSS",9,0,1204,225,172,6);//golpe saltando simple
		Animacion *patadaSS=new Animacion("patadaSS",9,0,1720,225,172,6);//patada saltando simple
		Animacion *golpeF=new Animacion("golpeF",7,0,1892,225,172,8);//golpe fuerte
		Animacion *patadaF=new Animacion("patadaF",9,0,2064,225,172,6);//patada fuerte
		Animacion *golpeAF=new Animacion("golpeAF",7,0,2236,225,172,8);//golpe agachado fuerte
		Animacion *patadaAF=new Animacion("patadaAF",5,0,2408,225,172,16);//patada agachado fuerte
		Animacion *golpeSF=new Animacion("golpeSF",7,0,2580,225,172,10);//golpe saltando fuerte
		Animacion *patadaSF=new Animacion("patadaSF",6,0,2752,225,172,10);//patada saltando fuerte
		Animacion *defensa=new Animacion("defensa",10,0,2924,225,172,8);
		Animacion *disparo=new Animacion("disparar",8,0,3268,225,172,8);
		Animacion *tiro=new Animacion("tirar",6,0,3440,225,172,8);
		Animacion *rgolpe=new Animacion("recibirGolpe",3,0,4128,225,172,8);
		animaciones.push_back(disparo);
		animaciones.push_back(tiro);
		animaciones.push_back(rgolpe);
		animaciones.push_back(defensa);		
		animaciones.push_back(golpeF);
		animaciones.push_back(patadaF);
		animaciones.push_back(golpeAF);
		animaciones.push_back(patadaAF);
		animaciones.push_back(golpeSF);
		animaciones.push_back(patadaSF);
		animaciones.push_back(golpeS);
		animaciones.push_back(patadaS);
		animaciones.push_back(golpeAS);
		animaciones.push_back(patadaAS);
		animaciones.push_back(golpeSS);
		animaciones.push_back(patadaSS);
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
		Animacion *quieto = new Animacion("quieto",6,0,0,225,172,10);
		Animacion *moverDerecha = new Animacion("movDerecha",12,0,172,225,172,4);
		Animacion *moverIzquierda = new Animacion("movIzquierda",12,0,344,225,172,4);
		Animacion *salto = new Animacion("salto",13,0,516,225,172,4);
		Animacion *agacharse = new Animacion("agacharse",10,0,688,225,172,2);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",12,0,1892,225,172,2);
		Animacion *golpeS=new Animacion("golpeS",4,0,860,225,172,6);//golpe simple
		Animacion *patadaS=new Animacion("patadaS",4,0,1032,225,172,8);//patada simple
		Animacion *golpeAS=new Animacion("golpeAS",4,0,1204,225,172,6);//golpe agachado simple
		Animacion *patadaAS=new Animacion("patadaAS",5,0,1376,225,172,6);//patada agachado simple
		Animacion *golpeSS=new Animacion("golpeSS",3,0,1548,225,172,8);//golpe saltando simple
		Animacion *patadaSS=new Animacion("patadaSS",4,0,1720,225,172,8);//patada saltando simple
		Animacion *golpeF=new Animacion("golpeF",8,0,2236,225,172,8);//golpe fuerte
		Animacion *patadaF=new Animacion("patadaF",8,0,2408,225,172,6);//patada fuerte
		Animacion *golpeAF=new Animacion("golpeAF",8,0,2580,225,172,8);//golpe agachado fuerte
		Animacion *patadaAF=new Animacion("patadaAF",7,0,2752,225,172,8);//patada agachado fuerte
		Animacion *golpeSF=new Animacion("golpeSF",8,0,2924,225,172,10);//golpe saltando fuerte
		Animacion *patadaSF=new Animacion("patadaSF",11,0,3096,225,172,10);//patada saltando fuerte
		Animacion *defensa=new Animacion("defensa",4,0,2064,225,172,8);
		Animacion *disparo=new Animacion("disparar",8,0,3268,225,172,8);
		Animacion *tiro=new Animacion("tirar",6,0,3440,225,172,8);
		Animacion *rgolpe=new Animacion("recibirGolpe",3,0,4128,225,172,8);
		animaciones.push_back(disparo);
		animaciones.push_back(tiro);
		animaciones.push_back(rgolpe);
		animaciones.push_back(defensa);		
		animaciones.push_back(golpeF);
		animaciones.push_back(patadaF);
		animaciones.push_back(golpeAF);
		animaciones.push_back(patadaAF);
		animaciones.push_back(golpeSF);
		animaciones.push_back(patadaSF);
		animaciones.push_back(golpeS);
		animaciones.push_back(patadaS);
		animaciones.push_back(golpeAS);
		animaciones.push_back(patadaAS);
		animaciones.push_back(golpeSS);
		animaciones.push_back(patadaSS);
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
		Animacion *moverIzquierda = new Animacion("movIzquierda",16,0,285,170,150,4);
		Animacion *salto = new Animacion("salto",10,0,580,170,215,6);
		Animacion *agacharse = new Animacion("agacharse",5,0,450,170,123,4);
		Animacion *cambioEntrada = new Animacion("cambioEntrada",8,0,1119,170,248,3);
		Animacion *golpeS=new Animacion("golpeS",5,0,450,170,123,4);//golpe simple
		Animacion *patadaS=new Animacion("patadaS",5,0,450,170,123,4);//patada simple
		Animacion *golpeAS=new Animacion("golpeAS",5,0,450,170,123,4);//golpe agachado simple
		Animacion *patadaAS=new Animacion("patadaAS",5,0,450,170,123,4);//patada agachado simple
		Animacion *golpeSS=new Animacion("golpeSS",5,0,450,170,123,4);//golpe saltando simple
		Animacion *patadaSS=new Animacion("patadaSS",5,0,450,170,123,4);//patada saltando simple
		Animacion *golpeF=new Animacion("golpeF",3,0,1032,225,172,8);//golpe fuerte
		Animacion *patadaF=new Animacion("patadaF",6,0,1204,225,172,6);//patada fuerte
		Animacion *golpeAF=new Animacion("golpeAF",3,0,1548,225,172,8);//golpe agachado fuerte
		Animacion *patadaAF=new Animacion("patadaAF",4,0,1376,225,172,16);//patada agachado fuerte
		Animacion *golpeSF=new Animacion("golpeSF",4,0,1892,225,172,10);//golpe saltando fuerte
		Animacion *patadaSF=new Animacion("patadaSF",4,0,1720,225,172,10);//patada saltando fuerte
		Animacion *defensa=new Animacion("defensa",1,1,1,1,1,1);
		Animacion *disparo=new Animacion("disparar",8,0,3268,225,172,8);
		Animacion *tiro=new Animacion("tirar",6,0,3440,225,172,8);
		Animacion *rgolpe=new Animacion("recibirGolpe",3,0,4128,225,172,8);
		animaciones.push_back(disparo);
		animaciones.push_back(tiro);
		animaciones.push_back(rgolpe);
		animaciones.push_back(defensa);		
		animaciones.push_back(golpeF);
		animaciones.push_back(patadaF);
		animaciones.push_back(golpeAF);
		animaciones.push_back(patadaAF);
		animaciones.push_back(golpeSF);
		animaciones.push_back(patadaSF);
		animaciones.push_back(golpeS);
		animaciones.push_back(patadaS);
		animaciones.push_back(golpeAS);
		animaciones.push_back(patadaAS);
		animaciones.push_back(golpeSS);
		animaciones.push_back(patadaSS);
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
		Animacion *golpeS=new Animacion("golpeS",1,0,0,600,600,2);//golpe simple
		Animacion *patadaS=new Animacion("patadaS",1,0,0,600,600,2);//patada simple
		Animacion *golpeAS=new Animacion("golpeAS",1,0,0,600,600,2);//golpe agachado simple
		Animacion *patadaAS=new Animacion("patadaAS",1,0,0,600,600,2);//patada agachado simple
		Animacion *golpeSS=new Animacion("golpeSS",1,0,0,600,600,2);//golpe saltando simple
		Animacion *patadaSS=new Animacion("patadaSS",1,0,0,600,600,2);//patada saltando simple
		Animacion *golpeF=new Animacion("golpeF",1,0,0,600,600,10);//golpe fuerte
		Animacion *patadaF=new Animacion("patadaF",1,0,0,600,600,10);//patada fuerte
		Animacion *golpeAF=new Animacion("golpeAF",1,0,0,600,600,10);//golpe agachado fuerte
		Animacion *patadaAF=new Animacion("patadaAF",1,0,0,600,600,10);//patada agachado fuerte
		Animacion *golpeSF=new Animacion("golpeSF",1,0,0,600,600,10);//golpe saltando fuerte
		Animacion *patadaSF=new Animacion("patadaSF",1,0,0,600,600,10);//patada saltando fuerte
		Animacion *defensa=new Animacion("defensa",1,0,0,600,600,10);
		Animacion *disparo=new Animacion("disparar",1,0,0,600,600,10);
		Animacion *tiro=new Animacion("tirar",1,0,0,600,600,10);
		Animacion *rgolpe=new Animacion("recibirGolpe",1,0,0,600,600,10);
		animaciones.push_back(disparo);
		animaciones.push_back(tiro);
		animaciones.push_back(rgolpe);
		animaciones.push_back(defensa);
		animaciones.push_back(golpeF);
		animaciones.push_back(patadaF);
		animaciones.push_back(golpeAF);
		animaciones.push_back(patadaAF);
		animaciones.push_back(golpeSF);
		animaciones.push_back(patadaSF);
		animaciones.push_back(golpeS);
		animaciones.push_back(patadaS);
		animaciones.push_back(golpeAS);
		animaciones.push_back(patadaAS);
		animaciones.push_back(golpeSS);
		animaciones.push_back(patadaSS);
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
	else if(nombre=="MegaManBoton"){
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
