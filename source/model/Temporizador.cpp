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
	this->tiempoBackup = 0;
}

Temporizador::~Temporizador(){

}

void Temporizador::resetear(){
	this->corriendo = true;
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

void Temporizador::frenar(){
	this->corriendo = false;
	this->tiempoBackup = this->tiempoTranscurrido;
}

void Temporizador::recuperar(){
	this->corriendo = true;
	this->resetear();
}
float Temporizador::getEscalaDeTiempo(){
	return this->escalaDeTiempo;
}

void Temporizador::actualizar(){
	if (!this->corriendo){
		return;
	}
	this->tiempoTranscurrido = (SDL_GetTicks() - this->tiempoInicial) + this->tiempoBackup;
	this->deltaTiempo = this->tiempoTranscurrido * 0.001f;
}

std::tuple<std::string, SDL_Rect, SDL_Rect ,SDL_RendererFlip > Temporizador::getDibujable(){
	SDL_Rect origen = {-1,-1,-1,-1};
	SDL_Rect destino = { this->ancho_ventana /2, (80 * this->alto_ventana) / this->alto_maximo_ventana,0,0};
	return make_tuple(std::string("Temporizador/") + to_string(controladorJson->TIEMPO_ROUND - int(this->getDeltaTiempo())),origen,destino,SDL_FLIP_NONE);

}

std::tuple<std::string, SDL_Rect, SDL_Rect ,SDL_RendererFlip > Temporizador::getDibujableMundo(){
	SDL_Rect origen = {0,0,1294,1294};
	SDL_Rect destino = { (this->ancho_ventana /2)-50, ((80 * this->alto_ventana) / this->alto_maximo_ventana)-30,100,100};
	return make_tuple(std::string("Mundo"),origen,destino,SDL_FLIP_NONE);

}

void Temporizador::finalizar(){
	this->corriendo = false;
	this->tiempoTranscurrido = controladorJson->TIEMPO_ROUND / 0.001f;
	this->deltaTiempo = controladorJson->TIEMPO_ROUND;
}
