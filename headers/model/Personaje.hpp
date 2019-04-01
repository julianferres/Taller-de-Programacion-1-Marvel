#ifndef PERSONAJE_HPP_
#define PERSONAJE_HPP_

#include <Juego.hpp>
#include <ConfiguracionGlobal.hpp>
#include <Sprite.hpp>
#include <ControladorGrafico.hpp>
#include <string>

using namespace std;

class Personaje{

	public:

		Personaje(ControladorGrafico &grafico,const string filepath, float x, float y);
		~Personaje();
		void dibujar(ControladorGrafico &grafico);
		void MoverDerecha();
		void MoverIzquierda();

	private:

		float posx, posy;
		Sprite sprite;

};

#endif

