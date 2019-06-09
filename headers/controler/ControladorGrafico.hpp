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

		ControladorGrafico(int idCliente);
		~ControladorGrafico();
		SDL_Surface* cargarImagen(const string &filePath);
		SDL_Renderer* getRenderer() const;
		void dibujarImagen(SDL_Texture* source, SDL_Rect* rectanguloOrigen, SDL_Rect* rectanguloDestino, SDL_RendererFlip flip);
		void render();
		void limpiar();
		void cambiarPantallaCompleta();
		void maximizarVentana(int ancho, int alto);
		void dibujarRectanguloDeColor(int red, int green, int blue, int alpha, SDL_Rect *rectangulo);

	private:

		SDL_Window* _window;
		SDL_Renderer* _renderer;
		map<string, SDL_Surface*> _spriteSheets;
		Uint32 sizePantalla = SDL_WINDOW_RESIZABLE;

};

#endif
