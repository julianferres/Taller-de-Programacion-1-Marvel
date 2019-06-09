#include <JuegoCliente.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include<iostream>

using namespace std;
extern ControladorJson *controladorJson;

JuegoCliente::JuegoCliente(){
	SDL_Init(0);
	SDL_VideoInit(NULL);
	SDL_InitSubSystem(SDL_INIT_TIMER);
	this->lifeBar = new LifeBar();
}

JuegoCliente::~JuegoCliente(){
	delete grafico;
	delete texturas;
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_VideoQuit();
	SDL_QuitSubSystem(SDL_INIT_TIMER);
	SDL_Quit();
}

ControladorGrafico* JuegoCliente::graficos(){
	return (this->grafico);
}

void JuegoCliente::cargarTexturas(vector<tuple<string, const string>> nombresYpaths){
	this->texturas = new Texturas(*grafico,nombresYpaths);
	//const string filepath = "sinSprite.png";
	//SDL_Texture* textura = SDL_CreateTextureFromSurface(grafico->getRenderer(),grafico->cargarImagen(filepath));
	//this->texturas->agregarTextura("SinSprite", textura );
	//filepath = "BotonSinSprite.jpg";
	//textura = SDL_CreateTextureFromSurface(grafico->getRenderer(),grafico->cargarImagen(filepath));
	//this->texturas->agregarTextura("BotonSinSprite", textura );
}

void JuegoCliente::cargarTitulosMenu(vector<tuple<string,string,int,string,int ,int ,int >>titulos){
	this->texturas->cargarTitulos(*grafico,titulos);
}

void JuegoCliente::iniciarGraficos(int idCliente){
	this->grafico = new ControladorGrafico(idCliente);
	this->anchoVentana = controladorJson->anchoVentana();
	this->altoVentana = controladorJson->alturaVentana();
}

SDL_Texture * JuegoCliente::getTextura(string nombre){
	return this->texturas->getTextura(nombre);
}

void JuegoCliente::dibujar(string nombre,int posiciones[8],SDL_RendererFlip flip){
	int w=0;
	int h=0;
	origen.x = posiciones[0];
	origen.y = posiciones[1];
	origen.w = posiciones[2];
	origen.h = posiciones[3];

	if(nombre=="Titulo" ||nombre=="SubTitulo" || nombre=="Eleccion")
		SDL_QueryTexture(getTextura(nombre), NULL, NULL,&w , &h);

	destino.x = posiciones[4]-(w/2);
	destino.y = posiciones[5];
	destino.w = posiciones[6]+w;
	destino.h = posiciones[7]+h;

	if(posiciones[0]==-1)
		this->grafico->dibujarImagen(getTextura(nombre),NULL, &destino, flip);
	else{
		this->grafico->dibujarImagen(getTextura(nombre),&origen, &destino, flip);
		lifeBar->actualizarPersonajesActuales(nombre);
	}
}

void JuegoCliente::dibujarBarrasVida(){
	string nombre = "";
	SDL_Rect fondoVida;
	for(int i = 0; i < 4; i++){
		if(i == 0) nombre = "CapitanAmerica";
		else if(i == 1) nombre = "Hulk";
		else if(i == 2) nombre = "Spiderman";
		else nombre = "Venom";

		destino.h = lifeBar->obtenerAnchoBarra(nombre);
		destino.w = lifeBar->obtenerLargoBarra(nombre, this->anchoVentana);
		destino.x = lifeBar->obtenerPosicionHorizontal(nombre, this->anchoVentana);
		destino.y = lifeBar->obtenerPosicionVertical(nombre);

		fondoVida.x = lifeBar->obtenerPosicionVerticalFondoVida(nombre);
		fondoVida.y = lifeBar->obtenerPosicionHorizontalFondoVida(nombre, this->anchoVentana);
		fondoVida.h = lifeBar->obtenerAnchoFondoVida(nombre);
		fondoVida.w = lifeBar->obtenerLargoFondoVida(nombre);

		this->grafico->dibujarImagen(getTextura(lifeBar->obtenerNombreBarra(nombre)), NULL,&destino, lifeBar->obtenerFlipBarra(nombre));
		this->grafico->dibujarRectanguloDeColor(255,255,0,150, &fondoVida);
	}
}





