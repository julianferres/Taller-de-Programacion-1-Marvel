#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <Juego.hpp>
#include <ConfiguracionGlobal.hpp>
#include <SpriteAnimado.hpp>
#include <ControladorGrafico.hpp>

class ControladorGrafico;
class Personaje: public SpriteAnimado{

public:
	Personaje();
	Personaje(ControladorGrafico &graficos, float x, float y);
//~Personaje();
	void update(float tiempoTrancurrido);
	void dibujar(ControladorGrafico &graficos);
	void MoverDerecha();
	void MoverIzquierda();
	/* void frenar
	 * El personaje frena mirando a la direccion ahacia la que venia caminando
	 */
	void Frenar();
	virtual void animacionFinalizada(std::string animacionActual);
	virtual void configurarAnimaciones();

private:
	float _dx, _dy;
	//int xpos;
	//int ypos;
//Direccion _direccion;
//	SDL_Texture* objTexture;
	//SDL_Rect srcRect, destRect;
};



#endif /* PERSONAJE_H_ */

//feature/personaje

