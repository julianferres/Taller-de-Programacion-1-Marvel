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
		void setearAnchoyAltoPantalla(int altoVentana, int anchoVentana);
		int obtenerAnchoBarra(string nombrePersonaje);
		int obtenerLargoBarra(string nombrePersonaje);
		int obtenerPosicionHorizontal(string nombrePersonaje);
		int obtenerPosicionVertical(string nombrePersonaje);
		SDL_RendererFlip obtenerFlipBarra(string nombrePersonaje);
		void actualizarPersonajesActuales(string nombrePersonaje);

		int obtenerAnchoFondoVida(string nombrePersonaje);
		int obtenerLargoFondoVida(string nombrePersonaje);
		int obtenerPosicionHorizontalFondoVida(string nombrePersonaje);
		int obtenerPosicionVerticalFondoVida(string nombrePersonaje);
		int obtenerPosicionHorizontalVida(string nombrePersonaje, int vida);
		void setearLados(int *ladosPersonajes);

	private:
		map<string, int> lados;
		map<string, int> alturas;
		map<string, string> companieros;
		int alturaVentana;
		int anchoVentana;
		int anchoBarraArriba, anchoBarraAbajo;
		int largoBarraArriba, largoBarraAbajo;
		int posicionHorizontalBarraIzq;
		int posicionVerticalBarraArriba, posicionVerticalBarraAbajo;


		int anchoFondoVidaArriba, anchoFondoVidaAbajo;
		int largoFondoVidaArriba, largoFondoVidaAbajo;
		int posicionVerticalFondoVidaArriba, posicionVerticalFondoVidaAbajo;
		int posicionHorizontalFondoVidaArribaIzq, posicionHorizontalFondoVidaAbajoIzq;


		int posicionHorizontalVidaArribaIzq, posicionHorizontalVidaAbajoIzq;
};

#endif /* HEADERS_MODEL_LIFEBAR_HPP_ */
