#include <Personaje.hpp>
#include <ControladorJson.hpp>
#include <string>
#include<math.h>
#include <ControladorLogger.hpp>
extern ControladorLogger *controladorLogger;

#define constanteDeAltura 39.2f //Viene de despejar la velocidad en funcion a una h_max = 2*alto
#define constanteTiempoCiclos 0.3
using namespace std;

Personaje::~Personaje(){
}

Personaje::Personaje(ControladorGrafico &graficos, string nombre, int posicionXinicial, SDL_RendererFlip flip){
	this->posx= posicionXinicial;
	this->posxrelativo=this->posx;
	this->alto = controladorJson->alturaPersonaje(nombre);
	this->ancho = controladorJson->anchoPersonaje(nombre);
	this->posy= controladorJson->alturaVentana() *9/16; //DEPENDE DEL FONDO Z3
	this->spriteAnimado=SpriteAnimado(graficos,controladorJson->pathImagen(nombre));
	this->spriteAnimado.cargarAnimaciones(nombre);
	this->spriteAnimado.iniciarAnimacion("quieto");
	this->velocidadInicial = sqrt(constanteDeAltura * alto);
	this->flip = flip;
}

void Personaje::dibujar(ControladorGrafico &graficos){
	if(saltando)
		this->Saltar();
	this->spriteAnimado.update();
	if(this->spriteAnimado.getAnimacionActual()=="movDerecha")
			this->spriteAnimado.dibujar(graficos,this->posxrelativo,this->posy,alto,ancho, this->flip);
	else if(this->spriteAnimado.getAnimacionActual()=="movIzquierda")
				this->spriteAnimado.dibujar(graficos,this->posxrelativo,this->posy,alto, ancho, this->flip);
	else
			this->spriteAnimado.dibujar(graficos,this->posx,this->posy,alto, ancho, this->flip);

}

void Personaje::MoverDerecha(){
	if(posx + ancho/2> controladorJson->anchoVentana() - ancho )
		return;
	if(!saltando)
		this->spriteAnimado.iniciarAnimacion("movDerecha");
	this->posxrelativo=this->posx;
	this->posx=this->posx+velocidad;
}

void Personaje::MoverIzquierda(){
	if(posx - ancho/2 < 0)
			return;
	if(!saltando)
		this->spriteAnimado.iniciarAnimacion("movIzquierda");
	this->posxrelativo=this->posx;
	this->posx=this->posx-velocidad;
}

void Personaje::agacharse(){
	this->spriteAnimado.iniciarAnimacion("agacharse");
}

void Personaje::Saltar(){
	this->spriteAnimado.iniciarAnimacion("salto");
	if( ! saltando) saltando = true;
	else{
		if(alturaActualSalto <= 0 && tiempo != 0 ){
			saltando = false; 	tiempo = 0; 	return;
		}
		else{
			tiempo += constanteTiempoCiclos;
			float alturaPrevia  = alturaActualSalto;
			alturaActualSalto = (velocidadInicial - 4.9* tiempo)*tiempo;
			//El 4.9 viene de 0.5*gravedad
			posy -= (alturaActualSalto - alturaPrevia);
		}
	}
}

float Personaje::getX(){
	return this->posx;
}

float Personaje::getXDer(){
	return (this->posx + this->ancho);
}

SDL_Rect  Personaje::obtenerRectangulo(){
	SDL_Rect rectangulo = { static_cast<int>(posx), static_cast<int>(posy), ancho, alto};
	return rectangulo;
}

bool Personaje::colisionaAlaDerecha(SDL_Rect rectanguloOponente){
	SDL_Rect rectanguloFuturo = { static_cast<int>(posx)+10, static_cast<int>(posy), ancho, alto};
	return SDL_HasIntersection( &rectanguloFuturo, &rectanguloOponente );
}

bool Personaje::colisionaAlaIzquierda(SDL_Rect rectanguloOponente){
	SDL_Rect rectanguloFuturo = { static_cast<int>(posx)-10, static_cast<int>(posy), ancho, alto};
	return SDL_HasIntersection( &rectanguloFuturo, &rectanguloOponente );
}


