#ifndef HEADERS_MODEL_JUEGOCLIENTE_HPP_
#define HEADERS_MODEL_JUEGOCLIENTE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorTeclado.hpp>
#include <Parallax.hpp>
#include <Texturas.hpp>
#include <LifeBar.hpp>


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
	void dibujarBarrasVida();

private:
	ControladorGrafico *grafico;
	Texturas *texturas;
	SDL_Rect origen;
	SDL_Rect destino;
	int anchoVentana;
	int altoVentana;
	LifeBar *lifeBar;
};



#endif
