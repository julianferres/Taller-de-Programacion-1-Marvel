#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class ControladorGrafico;

class Sprite{

	public:

		Sprite();
		Sprite( ControladorGrafico &graphicos, const std::string &filePath, int x0, int y0, int ancho, int alto);
		Sprite( ControladorGrafico &graphicos, const std::string &filePath, int x0, int y0, int ancho, int alto,float x,float y);
		virtual ~Sprite();
		virtual void update();
		void dibujar(ControladorGrafico &graphicos, int x, int y);

	protected:

		SDL_Rect _rectanguloOrigen;
		SDL_Texture* _spriteSheet;

};

#endif
