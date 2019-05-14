#ifndef HEADERS_MODEL_JUEGOCLIENTE_HPP_
#define HEADERS_MODEL_JUEGOCLIENTE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorTeclado.hpp>
#include <Parallax.hpp>
#include <Texturas.hpp>
#include <TexturasFondos.hpp>

class JuegoCliente{

public:
	JuegoCliente();
	~JuegoCliente();
	ControladorGrafico *graficos();
	TexturasFondos * fondos();
	SDL_Texture * getTextura(string nombre);
	void iniciarGraficos();
	void cargarTexturas(vector<tuple<string, const string>> nombresYpaths);
	void dibujar(std::string nombre,int posiciones[8],SDL_RendererFlip flip);

private:
	ControladorGrafico *grafico;
	TexturasFondos *texturasFondos;
	Texturas *texturas;
	SDL_Rect origen;
	SDL_Rect destino;

};



#endif
