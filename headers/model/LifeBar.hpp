#ifndef LIFEBAR_HPP_
#define LIFEBAR_HPP_

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class LifeBar{
	public:
		LifeBar();
		string obtenerPath(string nombrePersonaje);
		string obtenerNombreBarra(string nombrePersonaje);
		int obtenerLado(string nombrePersonaje);
		int obtenerAltura(string nombrePersonaje);

		int obtenerAnchoBarra(string nombrePersonaje);
		int obtenerLargoBarra(string nombrePersonaje, int anchoVentana);
		int obtenerPosicionHorizontal(string nombrePersonaje, int anchoVentana);
		int obtenerPosicionVertical(string nombrePersonaje);
		SDL_RendererFlip obtenerFlipBarra(string nombrePersonaje);
		void actualizarPersonajesActuales(string nombrePersonaje);

		int obtenerAnchoFondoVida(string nombrePersonaje);
		int obtenerLargoFondoVida(string nombrePersonaje);
		int obtenerPosicionHorizontalFondoVida(string nombrePersonaje, int anchoVentana);
		int obtenerPosicionVerticalFondoVida(string nombrePersonaje);

	private:
		map<string, int> lados;
		map<string, int> alturas;
		map<string, string> companieros;
		int posicionVerticalArriba = 10;
		int posicionVerticalAbajo = 85;
		int anchoBarraArriba = 70;
		int posicionHorizontalIzquierda = 10;

		int posicionHorizontalVidaIzq = 15;
		int posicionVerticalVidaArriba = 72;
		int posicionVerticalVidaAbajo = 150;
		int anchoFondoVidaArriba = 32;
		int largoFondoVida = 318;

};

#endif /* HEADERS_MODEL_LIFEBAR_HPP_ */
