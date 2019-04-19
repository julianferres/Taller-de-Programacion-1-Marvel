#ifndef HEADERS_MODEL_BOTON_HPP_
#define HEADERS_MODEL_BOTON_HPP_

#include <SDL2/SDL_image.h>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>

enum BotonSprite{
    BOTON_SPRITE_MOUSE_OUT = 0,
	BOTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BOTON_SPRITE_MOUSE_DOWN = 2,
	BOTON_SPRITE_MOUSE_UP = 3,
	BOTON_SPRITE_TOTAL = 4
};

class Boton{
public:
	Boton(int posX, int posY, int width, int heigth);
	~Boton();

	void setPosicion(int x, int y);
	void handleEvent(SDL_Event* e);
	void dibujar();

private:
	int width;
	int height;
	SDL_Point posicion;
	BotonSprite spriteActual;
};


#endif /* HEADERS_MODEL_BOTON_HPP_ */
