#ifndef parallax_hpp
#define parallax_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class Parallax{

public:
	static SDL_Event event;

	SDL_Window *window;

	bool running;
	const int FPS =30;
	const int SPEED = 5;
	int x,y;
	Uint32 start;
	SDL_Rect imgloc;
	SDL_Rect camera;
	SDL_Surface *background;
	SDL_Surface *image;
	SDL_Surface *screen;
	bool b[2];
	SDL_Texture *bitmapTex;

	//Constantes
	int W = 640;
	int H = 480;

	SDL_Renderer* renderer = nullptr;

	//Constructor
	Parallax(){
			SDL_Init(SDL_INIT_EVERYTHING); //usar para iniciar
			window = SDL_CreateWindow("paralax prueba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
			renderer = SDL_CreateRenderer(window,-1,0);
			if(renderer){
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			}
			screen = SDL_GetWindowSurface(window);


			this->running = true;

			start = SDL_GetTicks();

			x = 0;
			y = 0;

			background = SDL_LoadBMP("contents/images/city.bmp");
			image = SDL_LoadBMP("contents/images/tree_key.bmp");

			 bitmapTex = SDL_CreateTextureFromSurface(renderer, background);
			 SDL_FreeSurface(background);

			imgloc = {350,170,100,100};
			camera.x = 0;
			camera.y = 0;
			camera.w = W;
			camera.h = H;
			bool b[2] = {0,0};

			while(running) {
						start = SDL_GetTicks();
						SDL_Event event;
						while(SDL_PollEvent(&event)) {
							switch(event.type) {
								case SDL_QUIT:
									running = false;
									break;
								case SDL_KEYDOWN:
									switch(event.key.keysym.sym)
									{
										case SDLK_RIGHT:
											b[0] = 1;
											break;
										case SDLK_LEFT:
											b[1] = 1;
											break;
										case SDLK_ESCAPE:
											running = false;
											break;
									}
									break;
								case SDL_KEYUP:
									switch(event.key.keysym.sym)
									{
										case SDLK_RIGHT:
											b[0] = 0;
											break;
										case SDLK_LEFT:
											b[1] = 0;
											break;
									}
									break;
							}
						}

						//logic
						if(b[0])
						{
							x += SPEED;
							camera.x += SPEED;
							if(camera.x >= 2000-640)
								camera.x = 0;
						}
						else if(b[1])
						{
							x -= SPEED;
							camera.x -= SPEED;
							if(camera.x <= 0)
								camera.x = 2000-640;
						}

						SDL_Rect location = {x,y,640,480};
						SDL_Rect relcoord = {imgloc.x-x, imgloc.y-y};

						//render
				        SDL_RenderClear(renderer);
				        SDL_RenderCopy(renderer, bitmapTex, &camera, NULL);

						if(collision(&location, &imgloc))
							SDL_BlitSurface(image, NULL, screen, &relcoord);

						SDL_RenderPresent(renderer);
						if(1000/FPS > SDL_GetTicks()-start) {
							SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
						}
					}


	}

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

};

#endif
