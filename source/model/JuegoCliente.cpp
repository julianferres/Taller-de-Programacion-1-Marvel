#include <JuegoCliente.hpp>
#include<iostream>

using namespace std;

JuegoCliente::JuegoCliente(int idCliente){
	this->grafico = new ControladorGrafico(idCliente);
	this->sonido = new ControladorSonido();
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
	else
		this->grafico->dibujarImagen(getTextura(nombre),&origen, &destino, flip);

}

void JuegoCliente::correrSonido(const char* nombre){
	this->sonido->correrSonido(nombre);
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
