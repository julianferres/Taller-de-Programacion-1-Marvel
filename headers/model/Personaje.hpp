#ifndef PERSONAJE_HPP_
#define PERSONAJE_HPP_

#include <Juego.hpp>
#include <ConfiguracionGlobal.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>

class ControladorGrafico;
class Personaje{
public:
	Personaje();
	Personaje(ControladorGrafico &graficos, float x, float y);
	~Personaje();
	void dibujar(ControladorGrafico &graficos);
	void MoverDerecha();
	void MoverIzquierda();
private:
	float posx, posy;
};



#endif

