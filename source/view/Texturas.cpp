#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <map>
#include <tuple>
#include <SpriteAnimado.hpp>
#include <Texturas.hpp>
#include <iostream>

using namespace std;

Texturas::Texturas(ControladorGrafico &graficos,vector<tuple<string, const string>> nombresYpaths){
	for(size_t i=0;i<nombresYpaths.size();i++){
		tuple<string,const string> tuplai = nombresYpaths[i];
		const string &filePath = get<1>(tuplai);
		string nombre = get<0>(tuplai);
		 SDL_Texture *t1 =SDL_CreateTextureFromSurface(graficos.getRenderer(),graficos.cargarImagen(filePath));
		 texturas[nombre] = t1;
	}

}

SDL_Texture * Texturas::getTextura(string nombre){
	return this->texturas[nombre];
}


void Texturas::cargarTitulos(ControladorGrafico &graficos,vector<tuple<string,string,int,string,int ,int ,int >>titulos){
	TTF_Init();
	for(size_t i=0;i<titulos.size();i++){
		string nombre = get<0>(titulos[i]);
		string path = get<1>(titulos[i]);
		int size = get<2>(titulos[i]);
		string descripcion = get<3>(titulos[i]);
		SDL_Color color ={get<4>(titulos[i]),get<5>(titulos[i]),get<6>(titulos[i])};
		TTF_Font* font = TTF_OpenFont(path.c_str(),size);
		SDL_Surface* tituloSurface=TTF_RenderText_Solid(font,descripcion.c_str(), color);
		SDL_Texture *textura = SDL_CreateTextureFromSurface(graficos.getRenderer(),tituloSurface);
		texturas[nombre] = textura;
	}
}
