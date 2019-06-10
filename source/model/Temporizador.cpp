#include <Temporizador.hpp>
#include <GameMenu.hpp>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

Temporizador::Temporizador(){
	this->escalaDeTiempo = 1.0f;
	this->alto_ventana = controladorJson->alturaVentana();
	this->ancho_ventana = controladorJson->anchoVentana();
	this->resetear();
}

Temporizador::~Temporizador(){

}

void Temporizador::resetear(){
	this->tiempoInicial = SDL_GetTicks();
	this->tiempoTranscurrido = 0;
	this->deltaTiempo = 0;
}

float Temporizador::getDeltaTiempo(){
	return this->deltaTiempo;
}

void Temporizador::setEsacalDeTiempo(float escala){
	this->escalaDeTiempo = escala;

}

float Temporizador::getEscalaDeTiempo(){
	return this->escalaDeTiempo;
}

void Temporizador::actualizar(){
	this->tiempoTranscurrido = SDL_GetTicks() - this->tiempoInicial;
	this->deltaTiempo = this->tiempoTranscurrido * 0.001f;
}

std::tuple<std::string, SDL_Rect, SDL_Rect ,SDL_RendererFlip > Temporizador::getDibujable(){
	SDL_Rect origen = {-1,-1,-1,-1};
	SDL_Rect destino = { this->ancho_ventana /2, (80 * this->alto_ventana) / this->alto_maximo_ventana,0,0};
	return make_tuple(std::string("Temporizador/") + to_string(10-int(this->getDeltaTiempo())),origen,destino,SDL_FLIP_NONE);

}
