#include <JuegoCliente.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include<iostream>

using namespace std;

JuegoCliente::JuegoCliente(){
	SDL_Init(0);
	SDL_VideoInit(NULL);
	SDL_InitSubSystem(SDL_INIT_TIMER);
}

JuegoCliente::~JuegoCliente(){
	delete grafico;
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

	if(posiciones[4]==-1){
		this->grafico->dibujarImagen(getTextura(nombre),&origen, NULL, flip);
		return;
	}

	destino.x = posiciones[4]-(w/2);
	destino.y = posiciones[5];
	destino.w = posiciones[6]+w;
	destino.h = posiciones[7]+h;

	if(posiciones[0]==-1)
		this->grafico->dibujarImagen(getTextura(nombre),NULL, &destino, flip);
	else
		this->grafico->dibujarImagen(getTextura(nombre),&origen, &destino, flip);


}

