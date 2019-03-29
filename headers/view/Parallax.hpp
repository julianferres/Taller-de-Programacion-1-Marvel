#ifndef parallax_hpp
#define parallax_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class Parallax{

public:
	bool running;
	SDL_Surface *image;
	bool b[2];

	//Constructor
	Parallax();
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


private:
	const int FPS =60;
	const int SPEED_z1 = 5;
	const int SPEED_z2=  7.5;
	const int SPEED_z3 = 10;
	const int CAMERA_LIMIT = 2000;
	//Constantes (salen del JSON)
	int W = 640;
	int H = 480;



};
#endif


