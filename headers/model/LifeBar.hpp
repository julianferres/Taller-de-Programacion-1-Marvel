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

		int obtenerAnchoBarra(string nombrePersonaje, int alturaVentana);
		int obtenerLargoBarra(string nombrePersonaje, int anchoVentana);
		int obtenerPosicionHorizontal(string nombrePersonaje, int anchoVentana);
		int obtenerPosicionVertical(string nombrePersonaje, int alturaVentana);
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
		int posicionHorizontalIzquierda = 10;

		int posicionHorizontalVidaArribaIzq = 75;
		int posicionVerticalVidaArriba = 14;
		int posicionVerticalVidaAbajo = 88;
		int anchoFondoVidaArriba = 37;
		int largoFondoVida = 320;

};

#endif /* HEADERS_MODEL_LIFEBAR_HPP_ */
