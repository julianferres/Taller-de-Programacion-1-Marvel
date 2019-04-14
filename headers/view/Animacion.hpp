#ifndef ANIMACION_HPP_
#define ANIMACION_HPP_

#include <string>
#include <vector>
#include <SDL2/SDL_image.h>

class Animacion{

	public:

		Animacion();
		~Animacion();
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
