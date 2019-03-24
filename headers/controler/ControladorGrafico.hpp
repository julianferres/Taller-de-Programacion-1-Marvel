/*
 * ControladorGrafico.hpp
 *
 *  Created on: Mar 23, 2019
 *      Author: luupesado
 */

#ifndef HEADERS_VIEW_CONTROLADORGRAFICO_HPP_
#define HEADERS_VIEW_CONTROLADORGRAFICO_HPP_
//Toda la informacion necesaria para manejar los graficos

#include <map>
#include <string>
#include <SDL2/SDL_image.h>

struct SDL_Window;
struct SDL_Renderer;



class ControladorGrafico{
	public:
		ControladorGrafico();
		~ControladorGrafico();

		/*SDL_Surface* loadImage
		 * Carga una imagen al mapa de spritesheets si no existe todavia
		 * Entonces cada imagen solo se carga una vez
		 * Devuelve la imagen haya sido cargada recien o anteriormente
		 */
		SDL_Surface* cargarImagen(const std::string &filePath);

		/*void dibujarImagen
		 * Dibuja una textura en la pantalla
		 */

		void dibujarImagen(SDL_Texture* source, SDL_Rect* rectanguloOrigen, SDL_Rect* rectanguloDestino);

		/*void flip
		 * Renderiza todo a la pantalla
		 */
		void render();

		/*void clear
		 * Clears the screen
		 */
		void clear();
		/* SDL_Renderes getRenderer
		 * Returns the renderer
		 */

		SDL_Renderer* getRenderer() const;

	private:
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		std::map<std::string, SDL_Surface*> _spriteSheets;
};




#endif /* HEADERS_VIEW_CONTROLADORGRAFICO_HPP_ */
