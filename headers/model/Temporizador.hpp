#ifndef HEADERS_MODEL_TEMPORIZADOR_HPP_
#define HEADERS_MODEL_TEMPORIZADOR_HPP_
#include <SDL2/SDL_image.h>
#include <tuple>

class Temporizador{
//Singleton
private:
	//static Temporizador* isInstance;

	unsigned int tiempoInicial;
	unsigned int tiempoTranscurrido;
	unsigned int tiempoBackup;
	float deltaTiempo;
	float escalaDeTiempo;
	int ancho_ventana;
	int alto_ventana;
	int ancho_maximo_ventana = 1400;
	int alto_maximo_ventana = 1000;


public:
	//static Temporizador* Instance();
	//static void eliminar();

	Temporizador();
	~Temporizador();
	void resetear();
	float getDeltaTiempo();
	void setEsacalDeTiempo(float escala);
	float getEscalaDeTiempo();
	void actualizar();
	void frenar();
	void recuperar();
	bool corriendo;
	std::tuple<std::string,SDL_Rect, SDL_Rect ,SDL_RendererFlip > getDibujable();
	std::tuple<std::string,SDL_Rect, SDL_Rect ,SDL_RendererFlip > getDibujableMundo();



};



#endif
