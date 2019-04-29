#include <TexturasFondos.hpp>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>
#include <SDL2/SDL.h>
#include <ControladorGrafico.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;


TexturasFondos::TexturasFondos(ControladorGrafico &graficos){
	this->cargarFondos();
	this->cargarTexturas(graficos);
}

TexturasFondos::~TexturasFondos(){
	SDL_FreeSurface(background_z1);
	SDL_FreeSurface(background_z2);
	SDL_FreeSurface(background_z3);

}


void TexturasFondos::cargarFondos(){
	int cantidad_fondos = controladorJson->cantidadFondos();
	if (cantidad_fondos == 0){
		controladorLogger->registrarEvento("ERROR", "Parallax::No hay informacion de fondos en el json." + controladorJson->pathFondo(3));
		return;
	}
	for(int i=0; i<99; i++){
		std::string fondo = controladorJson->pathFondo(i);
		if(!fondo.empty() ){
			fondos.push_back(fondo);
			zindexs.push_back(i);
		}
	}

	if(fondos.size() < (size_t)cantidad_fondos ){
		controladorLogger->registrarEvento("ERROR", "Parallax::Rango de zindex no permitido (1-99). Se cargan imagenes por defecto ");
		background_z1 = IMG_Load("contents/auxiliar/capa1aux.png");
		background_z2 = IMG_Load("contents/auxiliar/capa2aux.png");
		background_z3 = IMG_Load("contents/auxiliar/capa3aux.png");
		return;
	}
	if (cantidad_fondos >=1)
		background_z1 = IMG_Load(fondos[0].c_str());
	if (cantidad_fondos >=2)
		background_z2 = IMG_Load(fondos[1].c_str());
	if (cantidad_fondos >=3)
		background_z3 = IMG_Load(fondos[2].c_str());

	if(background_z1 == NULL)
		controladorLogger->registrarEvento("ERROR", "Parallax::No se pudo cargar la imagen con zindex = "+ to_string(zindexs[0]));
	else
		controladorLogger->registrarEvento("DEBUG", "Parallax::Se cargo la imagen con zindex = " + to_string(zindexs[0]) +"; "+ fondos[0] );
	if(background_z2 == NULL)
		controladorLogger->registrarEvento("ERROR", "Parallax::No se pudo cargar la imagen con zindex = "+ to_string(zindexs[1]));
	else
		controladorLogger->registrarEvento("DEBUG", "Parallax::Se cargo la imagen con zindex = " + to_string(zindexs[1]) +"; "+ fondos[1] );
	if(background_z3 == NULL)
		controladorLogger->registrarEvento("ERROR", "Parallax::No se pudo cargar la imagen con zindex = "+ to_string(zindexs[2]));
	else
		controladorLogger->registrarEvento("DEBUG", "Parallax::Se cargo la imagen con zindex = " + to_string(zindexs[2]) +"; "+ fondos[2] );
}

void TexturasFondos::cargarTexturas(ControladorGrafico &graficos){
	if (background_z1)
		bitmapTex1 = SDL_CreateTextureFromSurface(graficos.getRenderer(), background_z1);
	if (background_z2)
		bitmapTex2 = SDL_CreateTextureFromSurface(graficos.getRenderer(), background_z2);
	if (background_z3)
		bitmapTex3 = SDL_CreateTextureFromSurface(graficos.getRenderer(), background_z3);

	if(bitmapTex1 == NULL)
		controladorLogger->registrarEvento("ERROR", "Parallax::No se pudo cargar la textura con zindex = "+ to_string(zindexs[0]) );
	else
		controladorLogger->registrarEvento("DEBUG", "Parallax::Se cargo la textura con zindex = " + to_string(zindexs[0]) );
	if(bitmapTex2 == NULL)
		controladorLogger->registrarEvento("ERROR", "Parallax::No se pudo cargar la textura con zindex = "+ to_string(zindexs[1]) );
	else
		controladorLogger->registrarEvento("DEBUG", "Parallax::Se cargo la textura con zindex = " + to_string(zindexs[1]) );
	if(bitmapTex3 == NULL)
			controladorLogger->registrarEvento("ERROR", "Parallax::No se pudo cargar la textura con zindex = "+ to_string(zindexs[2]) );
	else
		controladorLogger->registrarEvento("DEBUG", "Parallax::Se cargo la textura con zindex = " + to_string(zindexs[2]) );

}



SDL_Texture *TexturasFondos::backgroundz1() {
	return bitmapTex1;
}

SDL_Texture *TexturasFondos::backgroundz2(){
	return bitmapTex2;
}

SDL_Texture *TexturasFondos::backgroundz3(){
	return bitmapTex3;
}

std::vector<int> TexturasFondos::getzindexes(){
	return zindexs;
}


