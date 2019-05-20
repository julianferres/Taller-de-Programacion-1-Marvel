#ifndef HEADERS_MODEL_BOTON_HPP_
#define HEADERS_MODEL_BOTON_HPP_

#include <SDL2/SDL_image.h>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>
#include <SpriteAnimado.hpp>

enum BotonSprite{
    BOTON_SPRITE_MOUSE_OUT = 0,
	BOTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BOTON_SPRITE_MOUSE_DOWN = 2,
	BOTON_SPRITE_MOUSE_UP = 3,
//	BOTON_SPRITE_TOTAL = 4
};

class Boton{

	public:

		Boton( int posX, int posY, int width, int heigth, std::string nombre);
		~Boton();
		void setPosicion(int x, int y);
		void handleEvent(SDL_Event e);
		bool fueClickeado();
		std::string Nombre();
		tuple<string,SDL_Rect, SDL_Rect ,SDL_RendererFlip > getDibujable();

	private:

		bool botonClickeado;
		int width;
		int height;
		std::string nombre;
		SpriteAnimado *spriteAnimado;
		SDL_Point posicion;
		BotonSprite spriteActual;

};


#endif
