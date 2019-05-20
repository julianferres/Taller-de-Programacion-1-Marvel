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
		void handleEvent(SDL_Event e,int idCliente);
		vector<tuple<string,SDL_Rect, SDL_Rect ,SDL_RendererFlip >> getDibujables();
		vector<tuple<string,string,int,string,int ,int ,int >> getTitulos(int csocket);
		bool finalizado();
		map<int, string> getPersonajesElegidos();

	private:

		vector<Boton*> botones;
		map<int, string> personajesElegidos;
		map<int, bool> clientesYaEligieron;
		int ancho_ventana;
		int alto_ventana;
		int ancho_maximo_ventana = 1400;
		int alto_maximo_ventana = 1000;

};

#endif
