#include <JuegoCliente.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include<iostream>

using namespace std;
//SDL_Color color ={0,0,0};
extern ControladorJson *controladorJson;

JuegoCliente::JuegoCliente(int idCliente){
	this->grafico = new ControladorGrafico(idCliente);
	this->sonido = new ControladorSonido();
	this->lifeBar = new LifeBar();
	this->anchoVentana = controladorJson->anchoVentana();
	this->altoVentana = controladorJson->alturaVentana();
	this->lifeBar->setearAnchoyAltoPantalla(this->altoVentana, this->anchoVentana);
}

JuegoCliente::~JuegoCliente(){
	delete sonido;
	delete texturas;
	delete grafico;
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
	this->lifeBar->setearAnchoyAltoPantalla(this->altoVentana, this->anchoVentana);
}

SDL_Texture * JuegoCliente::getTextura(string nombre){
	string key = nombre.substr(0, nombre.find("/"));
	if (key == "Temporizador"){
		string tiempo = nombre.substr(nombre.find("/")+1, nombre.length());
		return this->getTimer(tiempo);
	}
	return this->texturas->getTextura(nombre);
}

SDL_Texture * JuegoCliente::getTimer(string tiempo){

	SDL_Color color ={255,255, 255};
	string path="contents/Fonts/Badaboom.TTF";
	TTF_Font* font = TTF_OpenFont(path.c_str(),50);
	SDL_Surface *surface = TTF_RenderText_Solid(font, tiempo.c_str(), color);
	SDL_Texture * textura = SDL_CreateTextureFromSurface(this->grafico->getRenderer(), surface);
	return textura;
}

void JuegoCliente::dibujar(string nombre,int posiciones[8],SDL_RendererFlip flip){
	int w=0;
	int h=0;
	origen.x = posiciones[0];
	origen.y = posiciones[1];
	origen.w = posiciones[2];
	origen.h = posiciones[3];
	string key = nombre.substr(0, nombre.find("/"));
	if(key=="Titulo" ||key=="SubTitulo" || key=="Eleccion" || key == "Temporizador"){
		SDL_QueryTexture(getTextura(nombre), NULL, NULL,&w , &h);
		//cout << "textura for " << key << "Queriada" << endl;
	}
	destino.x = posiciones[4]-(w/2);
	destino.y = posiciones[5];
	destino.w = posiciones[6]+w;
	destino.h = posiciones[7]+h;
	//cout << "rects for " << key << " listos" << endl;
	if(posiciones[0]==-1)
		this->grafico->dibujarImagen(getTextura(nombre),NULL, &destino, flip);
	else{
		this->grafico->dibujarImagen(getTextura(nombre),&origen, &destino, flip);
		lifeBar->actualizarPersonajesActuales(nombre);
	}
}

void JuegoCliente::correrSonido(const char* nombre){
	this->sonido->correrSonido(nombre);
}

void JuegoCliente::setearLados(int *lados){
	this->lifeBar->setearLados(lados);
}

void JuegoCliente::dibujarBarrasVida(int *vidas){
	string nombre = "";
	for(int i = 0; i < 4; i++){
		if(i == 0) nombre = "CapitanAmerica";
		else if(i == 1) nombre = "MegaMan";
		else if(i == 2) nombre = "Spiderman";
		else nombre = "Venom";
		destino.h = lifeBar->obtenerAnchoBarra(nombre);
		destino.w = lifeBar->obtenerLargoBarra(nombre);
		destino.x = lifeBar->obtenerPosicionHorizontal(nombre);
		destino.y = lifeBar->obtenerPosicionVertical(nombre);


		fondoVida.y = lifeBar->obtenerPosicionVerticalFondoVida(nombre);
		fondoVida.x = lifeBar->obtenerPosicionHorizontalFondoVida(nombre);
		fondoVida.h = lifeBar->obtenerAnchoFondoVida(nombre);
		fondoVida.w = lifeBar->obtenerLargoFondoVida(nombre);
		this->grafico->dibujarRectanguloDeColor(200,50,0,0, &fondoVida);
		vida.y = lifeBar->obtenerPosicionVerticalFondoVida(nombre);
		vida.x = lifeBar->obtenerPosicionHorizontalVida(nombre, vidas[i]);
		vida.h = lifeBar->obtenerAnchoFondoVida(nombre);
		vida.w = (lifeBar->obtenerLargoFondoVida(nombre) * vidas[i]) / 100;
		this->grafico->dibujarRectanguloDeColor(250, 250, 0, 0, &vida);
		this->grafico->dibujarImagen(getTextura(lifeBar->obtenerNombreBarra(nombre)), NULL,&destino, lifeBar->obtenerFlipBarra(nombre));

	}
}

void JuegoCliente::correrCancionFondo(const char* nombre,int repeticiones){
	this->sonido->correrCancionFondo(nombre,repeticiones);
}

void JuegoCliente::detenerCancion(){
	this->sonido->detenerCancion();
}

void JuegoCliente::finalizarCancion(){
	this->sonido->finalizarCancion();
}


void JuegoCliente::handleEvents(SDL_Event evento){
	if(evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_p)
			this->sonido->detenerCancion();

	else if(evento.key.keysym.sym == SDLK_F11)
		grafico->cambiarPantallaCompleta();
}
