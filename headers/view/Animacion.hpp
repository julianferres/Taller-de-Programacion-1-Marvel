#ifndef HEADERS_VIEW_ANIMACION_HPP_
#define HEADERS_VIEW_ANIMACION_HPP_

#include <string>
#include <vector>
#include <Sprite.hpp>


class Animacion{

	public:

		Animacion();
		Animacion(std::string nombre, int frames,int x,int y, int ancho, int alto,int velocidad );
		std::string getNombre();
		int getFrames();
		int getVelocidad();
		SDL_Rect getRectOrigen(int frameIndex);


	private:

		std::string nombre;
		std::vector<SDL_Rect> rectangulos;
		int velocidad;
		int frames;


};



#endif
