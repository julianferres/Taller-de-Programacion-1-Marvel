#ifndef CONTROLADORGRAFICO_HPP_
#define CONTROLADORGRAFICO_HPP_

#include <map>
#include <string>
#include <SDL2/SDL_image.h>

using namespace std;

struct SDL_Window;
struct SDL_Renderer;

class ControladorGrafico{

	public:

		ControladorGrafico();
		~ControladorGrafico();

		SDL_Surface* cargarImagen(const string &filePath);
		void dibujarImagen(SDL_Texture* source, SDL_Rect* rectanguloOrigen, SDL_Rect* rectanguloDestino);
		void render();
		void limpiar();
		SDL_Renderer* getRenderer() const;
		bool controlarColision(SDL_Rect rect1, SDL_Rect rect2);

	private:

		SDL_Window* _window;
		SDL_Renderer* _renderer;
		map<string, SDL_Surface*> _spriteSheets;

};

#endif
