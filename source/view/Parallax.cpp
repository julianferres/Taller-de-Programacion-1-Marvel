#include <Parallax.hpp>
#include <iostream>
#include <SDL2/SDL.h>
#include <ControladorGrafico.hpp>
#include <controler/ControladorJson.hpp>
#include <controler/ControladorLogger.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;
extern time_t my_time;
Parallax::Parallax(){}

Parallax::Parallax(ControladorGrafico &graficos){
	background_z1 = IMG_Load(controladorJson->pathImagen(1).c_str());
	background_z2 = IMG_Load(controladorJson->pathImagen(2).c_str());
	background_z3 = IMG_Load(controladorJson->pathImagen(3).c_str());
	if(background_z1 == NULL)
		controladorLogger->registrarEvento("ERROR", "No se pudo cargar la imagen con zindex = 1: " + controladorJson->pathImagen(1), ctime(&my_time));
	else
		controladorLogger->registrarEvento("DEBUG", "Se cargo la imagen con zindex = 1: " + controladorJson->pathImagen(1), ctime(&my_time));


	if(background_z2 == NULL)
		controladorLogger->registrarEvento("ERROR", "No se pudo cargar la imagen con zindex = 2: " + controladorJson->pathImagen(2), ctime(&my_time));
	else
		controladorLogger->registrarEvento("DEBUG", "Se cargo la imagen con zindex = 2: " + controladorJson->pathImagen(2), ctime(&my_time));


	if(background_z3 == NULL)
		controladorLogger->registrarEvento("ERROR", "No se pudo cargar la imagen con zindex = 3: " + controladorJson->pathImagen(3), ctime(&my_time));
	else
		controladorLogger->registrarEvento("DEBUG", "Se cargo la imagen con zindex = 3: " + controladorJson->pathImagen(3), ctime(&my_time));

	bitmapTex1 = SDL_CreateTextureFromSurface(graficos.getRenderer(), background_z1);
	bitmapTex2 = SDL_CreateTextureFromSurface(graficos.getRenderer(), background_z2);
	bitmapTex3 = SDL_CreateTextureFromSurface(graficos.getRenderer(), background_z3);

	SDL_Rect imgloc = {350,170,100,100};
	camera_z1.x = 0;  camera_z1.y = 0;
	camera_z1.w = W; camera_z1.h = H;

	camera_z2.x = 0;  camera_z2.y = 0;
	camera_z2.w = W; camera_z2.h = H;

	camera_z3.x = 0;  camera_z3.y = 0;
	camera_z3.w = W; camera_z3.h = H;

}


void Parallax::MoverCamaraDerecha(){
	if(camera_z1.x >= background_z1->w - W ||
		camera_z2.x >= background_z2->w-W ||
		camera_z3.x >= background_z3->w-W){
		return;
	}
		camera_z1.x += SPEED_z1;
		camera_z2.x += SPEED_z2;
		camera_z3.x += SPEED_z3;
}

void Parallax::MoverCamaraIzquierda(){
	if(camera_z1.x <= 0 || camera_z2.x <= 0 || camera_z3.x <= 0){
		return;
	}
	camera_z1.x -= SPEED_z1;
	camera_z2.x -= SPEED_z2;
	camera_z3.x -= SPEED_z3;
}

SDL_Rect *Parallax::Camaraz1(){
	return &camera_z1;
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


