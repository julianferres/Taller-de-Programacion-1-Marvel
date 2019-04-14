#include <Parallax.hpp>
#include <iostream>
#include <SDL2/SDL.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;


Parallax::Parallax(ControladorGrafico &graficos){

	this->cargarFondos();
	this->cargarTexturas(graficos);
	this->iniciarCamaras();

}

void Parallax::cargarFondos(){
	int cantidad_fondos = controladorJson->cantidadFondos();
	if (cantidad_fondos == 0){
		controladorLogger->registrarEvento("ERROR", "Parallax::No hay informacion de fondos en el json. Se cargara fondo negro." + controladorJson->pathFondo(3));
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
		background_z1 = IMG_Load("contents/auxiliar/capa1.png");
		background_z2 = IMG_Load("contents/auxiliar/capa2.png");
		background_z3 = IMG_Load("contents/auxiliar/capa3.png");
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

void Parallax::cargarTexturas(ControladorGrafico &graficos){
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

void Parallax::iniciarCamaras(){
	if (background_z1){
		camera_z1.x = background_z1->w/2 - W/2;
		camera_z1.y = 0;
		camera_z1.w = W;
		camera_z1.h = H;
		controladorLogger->registrarEvento("DEBUG", "Parallax::Camara 1 inicializada");
	}else{
		controladorLogger->registrarEvento("ERROR", "Parallax::Como no hay fondo, no se puede inicializar la camara");
	}
	if (background_z2){
		camera_z2.x = background_z2->w/2 -W/2;
		camera_z2.y = 0;
		camera_z2.w = W;
		camera_z2.h = H;
		controladorLogger->registrarEvento("DEBUG", "Parallax::Camara 2 inicializada");
	}else{
		controladorLogger->registrarEvento("DEBUG", "Parallax::Camara 1 inicializada");
	}
	if (background_z3){
		camera_z3.x = background_z3->w/2 - W/2;
		camera_z3.y = 0;
		camera_z3.w = W;
		camera_z3.h = H;
		controladorLogger->registrarEvento("DEBUG", "Parallax::Camara 3 inicializada");
	}else{
		controladorLogger->registrarEvento("ERROR", "Parallax::Como no hay 3 fondo3, no se puede inicializar la camara 3");
	}
}

void Parallax::MoverCamaraDerecha(){
	if(finDeEscenarioDerecha() ){
		return;
	}
	if (background_z1){
		camera_z1.x += SPEED_z1;
	}
	if(background_z2){
		camera_z2.x += SPEED_z2;
	}
	if(background_z3){
		camera_z3.x += SPEED_z3;
	}
}

void Parallax::MoverCamaraIzquierda(){
	if(finDeEscenarioIzquierda()){
		return;
	}
	if (background_z1){
		camera_z1.x -= SPEED_z1;
	}
	if(background_z2){
		camera_z2.x -= SPEED_z2;
	}
	if(background_z3){
		camera_z3.x -= SPEED_z3;
	}
}

SDL_Rect *Parallax::Camaraz1(){
	return &camera_z1;
}


bool Parallax::finDeEscenarioIzquierda(){
	bool finEscenario = false;
	if (background_z1){
		finEscenario = finEscenario || camera_z1.x <= 0;
	}
	if (background_z2){
		finEscenario = finEscenario || camera_z2.x <= 0;
	}
	if (background_z3){
		finEscenario = finEscenario || camera_z3.x <= 0;
	}
	return finEscenario;//camera_z1.x <= 0 || camera_z2.x <= 0 || camera_z3.x <= 0;
}

bool Parallax::finDeEscenarioDerecha(){
	bool finEscenario = false;
	if (background_z1){
		finEscenario = finEscenario || camera_z1.x >= background_z1->w - W;
	}
	if (background_z2){
		finEscenario = finEscenario || camera_z2.x >= background_z2->w - W ;
	}
	if (background_z3){
		finEscenario = finEscenario || camera_z3.x >= background_z3->w - W;
	}
	return finEscenario;
}


SDL_Rect *Parallax::Camaraz2(){
	return &camera_z2;
}

SDL_Rect *Parallax::Camaraz3(){
	return &camera_z3;
}

SDL_Texture *Parallax::Backgroundz1() {
	return bitmapTex1;
}

SDL_Texture *Parallax::Backgroundz2(){
	return bitmapTex2;
}

SDL_Texture *Parallax::Backgroundz3(){
	return bitmapTex3;
}


