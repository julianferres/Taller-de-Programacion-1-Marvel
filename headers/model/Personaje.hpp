#ifndef PERSONAJE_HPP_
#define PERSONAJE_HPP_

#include <Juego.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>
#include <string>
#include <ControladorJson.hpp>
using namespace std;
extern ControladorJson *controladorJson;

class ControladorGrafico;

class Personaje{

	public:
		int getFrameIndex();
		Personaje(ControladorGrafico &grafico, std::string nombre, int posicionXinicial, SDL_RendererFlip flip);
		~Personaje();
		void dibujar(ControladorGrafico &grafico);
		bool MoverDerecha(Personaje *enemigo, bool finEscenarioDerecha);
		bool MoverIzquierda(Personaje *enemigo,bool finEscenarioIzquierda);
		void CorrerADerecha();
		void CorrerAIzquierda();
		void Saltar();
		void Cambio();
		void agacharse();
		void detenerAnimacion();
		void cambiarAnimacion(string nombre);
		float getXDer();
		SDL_Rect  obtenerRectangulo();
		bool coliionaAlaDerecha(SDL_Rect rectanguloOponente);
		bool colisionaAlaIzquierda(SDL_Rect rectanguloOponente);
		void Flip();
		float getPosX();
		float getPosY();
		bool ladoDerecho();
	private:
		int posicionXinicial;
		float posx, posy;
		SpriteAnimado spriteAnimado;
		int ancho;
		int alto;
		int velocidad = 10;
		float velocidadInicial;
		bool saltando = false;
		float alturaActualSalto = 0;
		float tiempo = 0;
		SDL_RendererFlip flip;

};

#endif

