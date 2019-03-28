#include <iostream>
#include <Parallax.hpp>
#include <SDL2/SDL.h>

	//Constructor
Parallax::Parallax(){
			SDL_Init(SDL_INIT_EVERYTHING); //usar para iniciar
			SDL_Window* window = SDL_CreateWindow("paralax prueba", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H, 0);
			SDL_Renderer* renderer = nullptr;
			renderer = SDL_CreateRenderer(window,-1,0);
			if(renderer){
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			}
			SDL_Surface *screen = SDL_GetWindowSurface(window);


			this->running = true;

			Uint32 start = SDL_GetTicks();

			int x = 0; 	int y = 0;

			SDL_Surface *background_z1 = IMG_Load("contents/images/capa2.png");
			SDL_Surface *background_z2 = IMG_Load("contents/images/capa1.png");
			SDL_Surface *background_z3 = IMG_Load("contents/images/capa0.png");

			SDL_Texture *bitmapTex1 = SDL_CreateTextureFromSurface(renderer, background_z1);
			SDL_Texture *bitmapTex2 = SDL_CreateTextureFromSurface(renderer, background_z2);
			SDL_Texture *bitmapTex3 = SDL_CreateTextureFromSurface(renderer, background_z3);

			SDL_Rect imgloc = {350,170,100,100};
			SDL_Rect camera_z1 ; SDL_Rect camera_z2 ; SDL_Rect camera_z3;
			camera_z1.x = 0;  camera_z1.y = 0;
			camera_z1.w = W; camera_z1.h = H;

			camera_z2.x = 0;  camera_z2.y = 0;
			camera_z2.w = W; camera_z2.h = H;

			camera_z3.x = 0;  camera_z3.y = 0;
			camera_z3.w = W; camera_z3.h = H;

			bool b[2] = {0,0};

			while(running) {
						start = SDL_GetTicks();
						static SDL_Event event;
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
							if(camera_z1.x >= background_z1->w - W ||
								camera_z2.x >= background_z2->w-W ||
								camera_z3.x >= background_z3->w-W){
								continue;
							}
							camera_z1.x += SPEED_z1;
							camera_z2.x += SPEED_z2;
							camera_z3.x += SPEED_z3;
						}
						else if(b[1])
						{
							if(camera_z1.x <= 0 || camera_z2.x <= 0 || camera_z3.x <= 0){
								continue;
							}
							camera_z1.x -= SPEED_z1;
							camera_z2.x -= SPEED_z2;
							camera_z3.x -= SPEED_z3;
						}

						SDL_Rect location = {x,y,640,480};
						SDL_Rect relcoord = {imgloc.x-x, imgloc.y-y};

						//render
				        SDL_RenderClear(renderer);
				        SDL_RenderCopy(renderer, bitmapTex1, &camera_z1, NULL);
				        SDL_RenderCopy(renderer, bitmapTex2, &camera_z2, NULL);
				        SDL_RenderCopy(renderer, bitmapTex3, &camera_z3, NULL);


						if(collision(&location, &imgloc))
							SDL_BlitSurface(image, NULL, screen, &relcoord);

						SDL_RenderPresent(renderer);
						if(1000/FPS > SDL_GetTicks()-start) {
							SDL_Delay(1000/FPS-(SDL_GetTicks()-start));
						}
					}
}
