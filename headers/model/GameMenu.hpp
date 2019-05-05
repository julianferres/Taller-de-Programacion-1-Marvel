#ifndef HEADERS_MODEL_GAMEMENU_HPP_
#define HEADERS_MODEL_GAMEMENU_HPP_

#include <Boton.hpp>
#include <vector>
#include <SDL2/SDL_ttf.h>

class GameMenu{

	public:

		GameMenu(ControladorGrafico &graficos,int idCliente);
		~GameMenu();
		void crearBotones(ControladorGrafico &graficos);
		void crearBotonParaPersonaje(ControladorGrafico &graficos, int i);
		void handleEvent(ControladorGrafico &graficos);
		void dibujar(ControladorGrafico &graficos);
		void elegirPersonajes(ControladorGrafico &graficos);
		string personajeElegidoPorCliente();

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
		int ancho_ventana;
		int alto_ventana;
		int ancho_maximo_ventana = 1400;
		int alto_maximo_ventana = 1000;
		string personajeElegido;

};

#endif
