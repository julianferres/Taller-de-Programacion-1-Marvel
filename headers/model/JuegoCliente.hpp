#ifndef HEADERS_MODEL_JUEGOCLIENTE_HPP_
#define HEADERS_MODEL_JUEGOCLIENTE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorSonido.hpp>
#include <ControladorJson.hpp>
#include <ControladorTeclado.hpp>
#include <Texturas.hpp>
#include <LifeBar.hpp>

class JuegoCliente{

public:
	JuegoCliente(int idCliente);
	~JuegoCliente();
	ControladorGrafico *graficos();
	SDL_Texture * getTextura(string nombre);
	SDL_Texture * getTimer(string tiempo);
	SDL_Texture * getResultado(string resultado);
	void iniciarGraficos(int idCliente);
	void cargarTexturas(vector<tuple<string, const string>> nombresYpaths);
	void cargarTitulosMenu(vector<tuple<string,string,int,string,int ,int ,int >>titulos);
	void dibujar(std::string nombre,int posiciones[8],SDL_RendererFlip flip);
	void handleEvents(SDL_Event evento);
	void dibujarBarrasVida(int *vidas);
	void setearLados(string *lados);
	void dibujarRectanguloFuturo(SDL_Rect rectFuturo);

private:
	ControladorGrafico *grafico;
	ControladorSonido *sonido;
	Texturas *texturas;
	SDL_Rect origen;
	SDL_Rect destino;
	int anchoVentana;
	int altoVentana;
	LifeBar *lifeBar;
	SDL_Rect fondoVida;
	SDL_Rect vida;
	SDL_Texture **timer;
	SDL_Surface *texto;
	bool borrar=false;
};



#endif
