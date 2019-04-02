#ifndef PERSONAJE_HPP_
#define PERSONAJE_HPP_

#include <Juego.hpp>
#include <ConfiguracionGlobal.hpp>
#include <Sprite.hpp>
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
		float getX();
		float getXDer();
		int ancho;
		int alto;
		float velocidadInicial;
		bool saltando = false;
		float alturaActualSalto = 0;
		float tiempo = 0;

	private:

		float posx, posy;
		Sprite sprite;
		int getXInicial(std::string nombre);
		int getYInicial(std::string nombre);

};

#endif

