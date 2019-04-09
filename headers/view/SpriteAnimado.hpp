#ifndef SPRITEANIMADO_HPP_
#define SPRITEANIMADO_HPP_

#include <string>
#include <vector>
#include <Animacion.hpp>
using namespace std;

class ControladorGrafico;

class SpriteAnimado{

	public:

		SpriteAnimado();
		SpriteAnimado(ControladorGrafico &graficos, const string &filePath, string nombre);
		void iniciarAnimacion(string animacion);
		void update();
		void dibujar(ControladorGrafico &graficos, int x, int y,int alto, int ancho, SDL_RendererFlip flip);
		void cambiarAnimacion(string animacion);
		void agregarAnimacion(int frames, int x, int y, string nombre, int ancho, int alto);
		void pararAnimacion();
		void esVisible( bool visible);
		void animacionFinalizada();
		string getAnimacionActual();
		void cargarAnimaciones(string nombre);

	private:

		Animacion *animacionActual;
		vector<Animacion*> animaciones;
		SDL_Texture* spriteSheet;
		int frameIndex = 0;
		int regulador = 0;
		bool visible = true;

};

#endif
