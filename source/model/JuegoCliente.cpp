#include <JuegoCliente.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include<iostream>
#include <map>

using namespace std;
//SDL_Color color ={0,0,0};
extern ControladorJson *controladorJson;
extern ControladorSonido *controladorSonido;

JuegoCliente::JuegoCliente(int idCliente){
	this->grafico = new ControladorGrafico(idCliente);
	this->lifeBar = new LifeBar();
	this->anchoVentana = controladorJson->anchoVentana();
	this->altoVentana = controladorJson->alturaVentana();
	this->lifeBar->setearAnchoyAltoPantalla(this->altoVentana, this->anchoVentana);
}

JuegoCliente::~JuegoCliente(){
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
	if (key == "Resultados"){
		string resultado = nombre.substr(nombre.find("/")+1, nombre.length());
		return this->getResultado(resultado);
	}
	return this->texturas->getTextura(nombre);
}

SDL_Texture * JuegoCliente::getTimer(string tiempo){
	tiempo=tiempo.append(" ");
	if(!texturas->existeTextura(tiempo)){
		SDL_Color color ={0,0,0};
		string path="contents/Fonts/Badaboom.TTF";
		TTF_Font* font = TTF_OpenFont(path.c_str(),50);
		SDL_Surface *surface = TTF_RenderText_Solid(font, tiempo.c_str(), color);
		SDL_Texture* textura= SDL_CreateTextureFromSurface(this->grafico->getRenderer(), surface);
		texturas->agregarTextura(tiempo, textura);
	}
	return texturas->getTextura(tiempo);


}


SDL_Texture * JuegoCliente::getResultado(string resultado){
	if(!texturas->existeTextura(resultado)){
		SDL_Color color ={255,155,0};
		string path="contents/Fonts/Badaboom.TTF";
		TTF_Font* font = TTF_OpenFont(path.c_str(),90);
		SDL_Surface *surface = TTF_RenderText_Blended(font, resultado.c_str(), color);
		SDL_LockSurface(surface);
		SDL_PixelFormat* fmt = surface->format;
		Uint8 r, g, b, a;
		SDL_LockSurface(surface);
		unsigned bpp = fmt->BytesPerPixel;
		for (int y = 0; y < surface->h; ++y)
		for (int x = 0; x < surface->w; ++x) {
			// Get a pointer to the current pixel.
			Uint32* pixel_ptr = (Uint32 *)(	(Uint8 *)surface->pixels + y * surface->pitch + x * bpp);
			// Get the old pixel components.
			SDL_GetRGBA( *pixel_ptr, fmt, &r, &g, &b, &a);
			// Set the pixel with the new alpha.
			*pixel_ptr = SDL_MapRGBA( fmt, r, g + Uint8(y%100), b, a);
		}
		SDL_UnlockSurface(surface);
		SDL_Texture * textura = SDL_CreateTextureFromSurface(this->grafico->getRenderer(), surface);
		texturas->agregarTextura(resultado, textura);
	}
	return texturas->getTextura(resultado);
}

void JuegoCliente::dibujarRectanguloFuturo(SDL_Rect rectFuturo){
	SDL_RenderDrawRect(this->grafico->getRenderer(),&rectFuturo);
}

void JuegoCliente::dibujar(string nombre,int posiciones[8],SDL_RendererFlip flip){
	int w=0;
	int h=0;
	origen.x = posiciones[0];
	origen.y = posiciones[1];
	origen.w = posiciones[2];
	origen.h = posiciones[3];
	string key = nombre.substr(0, nombre.find("/"));
	if(key=="Titulo" ||key=="SubTitulo" || key=="Eleccion" || key == "Temporizador" || key == "Resultados" || key == "Winners"){
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


void JuegoCliente::setearLados(string *lados){
	this->lifeBar->setearLados(lados);
}

void JuegoCliente::dibujarBarrasVida(int *vidas){
	string nombre = "";
	for(int i = 0; i < 4; i++){
		nombre = lifeBar->obtenerNombre(i);
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

		destino.w = destino.w / 2;
		destino.h = destino.h / 2;
		destino.x = lifeBar->obtenerPosicionHorizontalNombre(nombre);
		destino.y = lifeBar->obtenerPosicionVerticalNombre(nombre);
		this->grafico->dibujarImagen(getTextura(lifeBar->obtenerNombreParaBarra(nombre)), NULL, &destino, SDL_FLIP_NONE);
	}
}

void JuegoCliente::handleEvents(SDL_Event evento){
	if(evento.type == SDL_KEYDOWN && evento.key.keysym.sym == SDLK_p)
		controladorSonido->detenerCancion();

}
