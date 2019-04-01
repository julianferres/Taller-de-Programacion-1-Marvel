#ifndef PERSONAJE_HPP_
#define PERSONAJE_HPP_

#include <Juego.hpp>
#include <ConfiguracionGlobal.hpp>
#include <Sprite.hpp>
#include <SpriteAnimado.hpp>
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
private:
	float posx, posy;
	Sprite sprite;
	std::string getFilePath(std::string nombre);
	int getXInicial(std::string nombre);
	int getYInicial(std::string nombre);
	int getAncho(std::string nombre);
	int getAlto(std::string nombre);
};


//test
#endif

