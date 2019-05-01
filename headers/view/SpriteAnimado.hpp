#ifndef SPRITEANIMADO_HPP_
#define SPRITEANIMADO_HPP_

#include <string>
#include <vector>
#include <Animacion.hpp>

using namespace std;

class ControladorGrafico;
class Animacion;

class SpriteAnimado{

	public:

		~SpriteAnimado();
		SpriteAnimado(string nombre);
		bool iniciarAnimacion(string animacion);
		void update();
		void dibujar(ControladorGrafico &graficos, int x, int y,int alto, int ancho, SDL_RendererFlip flip);
		void cambiarAnimacion(string animacion);
		void agregarAnimacion(int frames, int x, int y, string nombre, int ancho, int alto);
		void pararAnimacion();
		void animacionFinalizada();
		void cargarAnimaciones(string nombre);
		int getFrameIndex();
		string getAnimacionActual();
		string getNombre();
		SDL_Rect rectOrigen();


	private:

		Animacion *animacionActual;
		vector<Animacion*> animaciones;
		SDL_Texture* spriteSheet;
		SDL_Surface* surface;
		int frameIndex = 0;
		int regulador = 0;
		bool visible = true;
		string nombreSprite;

};

#endif
