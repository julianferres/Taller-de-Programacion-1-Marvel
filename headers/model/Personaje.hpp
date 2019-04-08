#ifndef PERSONAJE_HPP_
#define PERSONAJE_HPP_

#include <Juego.hpp>
#include <ConfiguracionGlobal.hpp>
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
		void MoverDerecha();
		void MoverIzquierda();
		void Saltar();
		void agacharse();
		float getX();
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

