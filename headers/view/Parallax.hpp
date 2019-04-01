#ifndef parallax_hpp
#define parallax_hpp

#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>

extern ControladorJson *controladorJson;

class Parallax{

	public:

		SDL_Rect camera_z1 ; SDL_Rect camera_z2 ; SDL_Rect camera_z3;
		SDL_Surface *background_z1 ;
		SDL_Surface *background_z2;
		SDL_Surface *background_z3;
		SDL_Surface *image;
		SDL_Texture *bitmapTex1 ;
		SDL_Texture *bitmapTex2 ;
		SDL_Texture *bitmapTex3 ;

		void MoverCamaraIzquierda();
		void MoverCamaraDerecha();
		SDL_Rect *Camaraz1();
		SDL_Rect *Camaraz2();
		SDL_Rect *Camaraz3();
		SDL_Texture *Backgroundz1();
		SDL_Texture *Backgroundz2();
		SDL_Texture *Backgroundz3();

		Parallax();
		Parallax(ControladorGrafico &graficos);

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

		int W = controladorJson->anchoVentana();
		int H = controladorJson->alturaVentana();
		const int SPEED_z1 = 5;
		const int SPEED_z2=  7.5;
		const int SPEED_z3 = 10;
		const int CAMERA_LIMIT = 2000;
		int x = 0; 	int y = 0;


};
#endif


