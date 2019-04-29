#ifndef HEADERS_MODEL_JUEGOCLIENTE_HPP_
#define HEADERS_MODEL_JUEGOCLIENTE_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorTeclado.hpp>
#include <Parallax.hpp>
#include <TexturasFondos.hpp>

class JuegoCliente{

public:
	JuegoCliente();
	~JuegoCliente();
	ControladorGrafico *graficos();
	TexturasFondos * fondos();

private:
	ControladorGrafico *grafico;
	TexturasFondos *texturasFondos;

};



#endif
