#ifndef PERSONAJE_HPP_
#define PERSONAJE_HPP_

#include <Juego.hpp>
#include <ConfiguracionGlobal.hpp>
#include <Sprite.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>
#include <string>
#include <ControladorJson.hpp>

extern ControladorJson *controladorJson;

class ControladorGrafico;

class Personaje{

	public:

		Personaje(ControladorGrafico &grafico, std::string nombre);
		~Personaje();
		void dibujar(ControladorGrafico &grafico);
		void MoverDerecha();
		void MoverIzquierda();
		void Saltar();
		void agacharse();
		float getX();
		float getXDer();
		int ancho;
		int alto;
		float velocidadInicial;
		bool saltando = false;
		float alturaActualSalto = 0;
		float tiempo = 0;

	private:

		float posx, posy,posxrelativo;
		//Sprite sprite;
		SpriteAnimado spriteAnimado;

};

#endif

