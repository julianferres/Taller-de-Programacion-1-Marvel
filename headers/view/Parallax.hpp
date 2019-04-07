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

	private:

		int W = controladorJson->anchoVentana();
		int H = controladorJson->alturaVentana();
		const int SPEED_z1 = 5;
		const int SPEED_z2=  7.2;
		const int SPEED_z3 = 10;
		int x = 0; 	int y = 0;


};
#endif


