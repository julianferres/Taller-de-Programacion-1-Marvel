#ifndef HEADERS_MODEL_JUEGOCLIENTE_HPP_
#define HEADERS_MODEL_JUEGOCLIENTE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorTeclado.hpp>
#include <Parallax.hpp>
#include <Texturas.hpp>

class JuegoCliente{

public:
	JuegoCliente();
	~JuegoCliente();
	ControladorGrafico *graficos();
	SDL_Texture * getTextura(string nombre);
	void iniciarGraficos(int idCliente);
	void cargarTexturas(vector<tuple<string, const string>> nombresYpaths);
	void cargarTitulosMenu(vector<tuple<string,string,int,string,int ,int ,int >>titulos);
	void dibujar(std::string nombre,int posiciones[8],SDL_RendererFlip flip);
	void correrCancion(const char* nombre);
	void detenerCancion();
	void handleEvents(SDL_Event evento);

private:
	ControladorGrafico *grafico;
	Texturas *texturas;
	SDL_Rect origen;
	SDL_Rect destino;

};



#endif
