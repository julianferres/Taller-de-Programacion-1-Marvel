#include <Parallax.hpp>
#include <iostream>
#include <SDL2/SDL.h>
#include <ControladorGrafico.hpp>


Parallax::Parallax(){}

Parallax::Parallax(ControladorGrafico &graficos){


			background_z1 = IMG_Load("contents/images/capa2.png");
			background_z2 = IMG_Load("contents/images/capa1.png");
			background_z3 = IMG_Load("contents/images/capa0.png");

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


