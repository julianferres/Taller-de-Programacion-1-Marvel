#ifndef PERSONAJE_HPP_
#define PERSONAJE_HPP_

#include <Juego.hpp>
#include <ConfiguracionGlobal.hpp>
#include <Sprite.hpp>
#include <ControladorGrafico.hpp>
#include <string>


class ControladorGrafico;

class Personaje{

	public:

		Personaje(ControladorGrafico &grafico, std::string nombre);
		~Personaje();
		void dibujar(ControladorGrafico &grafico);
		void MoverDerecha();
		void MoverIzquierda();
		float getX();
		float getXDer();
		int ancho;
		int alto;


	private:

		float posx, posy;
		Sprite sprite;
		int getXInicial(std::string nombre);
		int getYInicial(std::string nombre);

};

#endif

