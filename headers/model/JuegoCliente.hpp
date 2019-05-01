#ifndef HEADERS_MODEL_JUEGOCLIENTE_HPP_
#define HEADERS_MODEL_JUEGOCLIENTE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorTeclado.hpp>
#include <Parallax.hpp>
#include <TexturasFondos.hpp>
#include <TexturasPersonajes.hpp>

class JuegoCliente{

public:
	JuegoCliente();
	~JuegoCliente();
	ControladorGrafico *graficos();
	TexturasFondos * fondos();
	void iniciarGraficos();
	void cargarTexturasJugadores(vector<tuple<string, const string>> nombresYpaths);

private:
	ControladorGrafico *grafico;
	TexturasFondos *texturasFondos;
	TexturasPersonajes *texturasPersonajes;

};



#endif
