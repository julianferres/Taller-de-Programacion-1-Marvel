#ifndef HEADERS_MODEL_GAMEMENU_HPP_
#define HEADERS_MODEL_GAMEMENU_HPP_

#include <Boton.hpp>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <string>

using namespace std;


class GameMenu{

	public:

		GameMenu();
		~GameMenu();
		void crearBotones();
		void crearBotonParaPersonaje( int i);
		void handleEvent(SDL_Event e);
		vector<tuple<string,SDL_Rect, SDL_Rect ,SDL_RendererFlip >> getDibujables();
		vector<tuple<string,char*,int,char*,int ,int ,int >> getTitulos();

	private:

		std::vector<Boton*> botones;
		TTF_Font* marvelFont;
		TTF_Font* selectFont;
		TTF_Font* pixelFont;
		SDL_Surface* tituloSurface;
		SDL_Texture* tituloTexture;
		SDL_Surface* subTituloSurface;
		SDL_Texture* subTituloTexture;
		SDL_Surface* actionSurface;
		SDL_Texture* actionTexture;
		vector<string> personajesElegidos;
		int ancho_ventana;
		int alto_ventana;
		int ancho_maximo_ventana = 1400;
		int alto_maximo_ventana = 1000;

};

#endif
