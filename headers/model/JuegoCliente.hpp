#ifndef HEADERS_MODEL_JUEGOCLIENTE_HPP_
#define HEADERS_MODEL_JUEGOCLIENTE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorSonido.hpp>
#include <ControladorJson.hpp>
#include <ControladorTeclado.hpp>
#include <Texturas.hpp>

class JuegoCliente{

public:
	JuegoCliente(int idCliente);
	~JuegoCliente();
	ControladorGrafico *graficos();
	SDL_Texture * getTextura(string nombre);
	void cargarTexturas(vector<tuple<string, const string>> nombresYpaths);
	void cargarTitulosMenu(vector<tuple<string,string,int,string,int ,int ,int >>titulos);
	void dibujar(std::string nombre,int posiciones[8],SDL_RendererFlip flip);
	void handleEvents(SDL_Event evento);
	void correrCancion(const char* nombre,int repeticiones);
	void detenerCancion();

private:
	ControladorGrafico *grafico;
	ControladorSonido *sonido;
	Texturas *texturas;
	SDL_Rect origen;
	SDL_Rect destino;

};



#endif
