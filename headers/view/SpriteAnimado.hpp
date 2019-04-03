#ifndef HEADERS_VIEW_SPRITEANIMADO_HPP_
#define HEADERS_VIEW_SPRITEANIMADO_HPP_

#include <Sprite.hpp>
#include <map>
#include <string>
#include <vector>
#include <ConfiguracionGlobal.hpp>
using namespace std;

class ControladorGrafico;

class SpriteAnimado{

	public:

		SpriteAnimado();
		SpriteAnimado(ControladorGrafico &graficos, const string &filePath);
		void iniciarAnimacion(string animacion, bool unica = false);
		void update(int largo);
		void dibujar(ControladorGrafico &graficos, int x, int y);
		void agregarAnimacion(int frames, int x, int y, string nombre, int ancho, int alto);
		void reiniciarAnimacion();
		void pararAnimacion();
		void esVisible( bool visible);
		void animacionFinalizada(string _animacionActual);

	private:

		map<string,vector<SDL_Rect> > animacion;
		map<std::string, Vector2> _offsets;
		double tiempoTrancurrido;

		int ancho;
		int alto;
		bool animacionActualUnica;
		double _timeToUpdate;
		string animacionActual;

		int frameIndex;
		bool visible;
		SDL_Texture* spriteSheet;

};

#endif
