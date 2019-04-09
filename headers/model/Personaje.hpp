#ifndef PERSONAJE_HPP_
#define PERSONAJE_HPP_

#include <Juego.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>
#include <string>
#include <ControladorJson.hpp>

extern ControladorJson *controladorJson;

class ControladorGrafico;

class Personaje{

	public:

		Personaje(ControladorGrafico &grafico, std::string nombre, int posicionXinicial, SDL_RendererFlip flip);
		~Personaje();
		void dibujar(ControladorGrafico &grafico);
		bool MoverDerecha(Personaje *enemigo, bool finEscenarioDerecha);
		bool MoverIzquierda(Personaje *enemigo,bool finEscenarioIzquierda);
		void CorrerADerecha();
		void CorrerAIzquierda();
		void Saltar();
		void agacharse();
		float getXDer();
		SDL_Rect  obtenerRectangulo();
		bool colisionaAlaDerecha(SDL_Rect rectanguloOponente);
		bool colisionaAlaIzquierda(SDL_Rect rectanguloOponente);

	private:

		float posx, posy,posxrelativo;
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

