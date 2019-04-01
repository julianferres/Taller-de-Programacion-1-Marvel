#include <Personaje.hpp>
#include <string>


Personaje::~Personaje(){

}
Personaje::Personaje(ControladorGrafico &graficos, std::string nombre){
	this->posx= jugador1::X0;
	this->posy= jugador1::YO;
	this->sprite=Sprite(graficos,this->getFilePath(nombre),this->getXInicial(nombre),
			this->getYInicial(nombre),this->getAncho(nombre),this->getAlto(nombre));

}
void Personaje::dibujar(ControladorGrafico &graficos){
	this->sprite.dibujar(graficos,this->posx,this->posy);
}
void Personaje::MoverDerecha(){
	this->posx=this->posx+30;
}

void Personaje::MoverIzquierda(){
	this->posx=this->posx-30;
}

std::string Personaje::getFilePath(std::string nombre){
	if( nombre == "CapitanAmerica"){
		return  "contents/images/CaptainAmericaSprites.png";
	}else if (nombre == "Spiderman"){
		return "contents/images/SpidermanSprites.png";
	}else{
		return "ERROR";
	}
}

int Personaje::getXInicial(std::string nombre){
	if( nombre == "CapitanAmerica"){
		return 7;
	}else if (nombre == "Spiderman"){
		return 11;
	}else{
		return 1;
	}
}

int Personaje::getYInicial(std::string nombre){
	if( nombre == "CapitanAmerica"){
		return 20;
	}else if (nombre == "Spiderman"){
		return 11;
	}else{
		return 1;
	}
}

int Personaje::getAlto(std::string nombre){
	if( nombre == "CapitanAmerica"){
		return 115;
	}else if (nombre == "Spiderman"){
		return 97;
	}else{
		return 1;
	}
}

int Personaje::getAncho(std::string nombre){
	if( nombre == "CapitanAmerica"){
		return 89;
	}else if (nombre == "Spiderman"){
		return 107;
	}else{
		return 1;
	}
}
