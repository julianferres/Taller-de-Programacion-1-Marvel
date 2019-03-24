/*
 * Srprite.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: matiscakosky
 */


#include <iostream>
#include <Parallax.hpp>
#include <SDL2/SDL.h>


//Constantes
int ANCHO = 600;
int ALTO = 800;
SDL_Renderer* Parallax::renderer = nullptr;

//Constructor
Parallax::Parallax(){
	SDL_Init(SDL_INIT_EVERYTHING);
		SDL_Surface *screen, *background, *image;
		window = SDL_CreateWindow("PRUEBA PARRALOX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ANCHO, ALTO, 0);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if(renderer){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		this->running = true;

		start = SDL_GetTicks();
		int x,y;
		x = 0;
		y = 0;

		background = SDL_LoadBMP("contents/images/city.bmp");
		image = SDL_LoadBMP("tree_key.bmp");
		imgloc = {350,170,100,100};
		camera.x = 0;
		camera.y = 0;
		camera.w = 640;
		camera.h = 480;
		bool b[2] = {0,0};

}

//Destructor
Parallax::~Parallax()
{}



/*Hay que entender bien que es lo que hace esta funcion*/

bool collision(SDL_Rect* rect1,SDL_Rect* rect2)
{
	if(rect1->y >= rect2->y + rect2->h)
		return 0;
	if(rect1->x >= rect2->x + rect2->w)
		return 0;
	if(rect1->y + rect1->h <= rect2->y)
		return 0;
	if(rect1->x + rect1->w <= rect2->x)
		return 0;
	return 1;
}
