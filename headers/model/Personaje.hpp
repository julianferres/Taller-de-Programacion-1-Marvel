#ifndef PERSONAJE_HPP_
#define PERSONAJE_HPP_

#include <Juego.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>
#include <string>
#include <ControladorJson.hpp>
#include <ControladorSonido.hpp>

using namespace std;

class ControladorGrafico;

class Personaje{

	public:

		Personaje( std::string nombre, int posicionXinicial, SDL_RendererFlip flip);
		~Personaje();
		int zindexPersonaje();
		void actualizar();
		bool moverDerecha(Personaje *enemigo, bool finEscenarioDerecha);
		bool moverIzquierda(Personaje *enemigo,bool finEscenarioIzquierda);
		bool colisionaAlaDerecha(SDL_Rect rectanguloOponente);
		bool colisionaAlaIzquierda(SDL_Rect rectanguloOponente);
		bool ladoDerecho();
		bool estaSaltando();
		void correrADerecha();
		void correrAIzquierda();
		void saltar();
		void cambio();
		void golpe(string tipoDeGolpe);
		void agacharse();
		void tirar();
		void cambiarAnimacion(string nombre);
		void Flip();
		void recibirGolpe();
		void defenderse();
		void disparar();
		SDL_RendererFlip getFlip();
		void actualizarPiso();
		float getPosX();
		float getPosY();
		SDL_Rect  obtenerRectangulo();
		std::string getNombre();
		string getSonido();
		SpriteAnimado *obtenerSprite();
		void restarVida(int cantidad);
		int obtenerVida();
		void setSonido(string animacion);

	private:

		int posicionXinicial;
		int zindex;
		int ancho;
		int alto;
		int velocidad = 10;
		int posicionYdefault ;
		float posx, posy;
		float velocidadInicial;
		float alturaActualSalto = 0;
		float tiempo = 0;
		bool agachado = false;
		bool saltando = false;
		bool defendiendo = false;
		SpriteAnimado *spriteAnimado;
		SDL_RendererFlip flip;
		std::string nombre;
		int vida;
		string sonidoAnimacion="";
};

#endif

