#ifndef HEADERS_VIEW_SPRITEANIMADO_HPP_
#define HEADERS_VIEW_SPRITEANIMADO_HPP_

#include <Sprite.hpp>
#include <map>
#include <string>
#include <vector>
#include <ConfiguracionGlobal.hpp>

class ControladorGrafico;

class SpriteAnimado: public Sprite{

	public:

		SpriteAnimado();
		SpriteAnimado(ControladorGrafico &graficos, const std::string &filePath, int x0, int y0, int ancho, int alto,float posX, float posY, float timeToUpdate);
		void iniciarAnimacion(std::string animacion, bool unica = false);
		void update(int tiempoTrancurrido);
		void dibujar(ControladorGrafico &graficos, int x, int y);

	protected:

		bool _animacionActualUnica;
		double _timeToUpdate;
		std::string _animacionActual;
		void agregarAnimacion(int frames, int x, int y, std::string nombre, int ancho, int alto, Vector2 offset);
		void reiniciarAnimacion();
		void pararAnimacion();
		void esVisible( bool visible);
		virtual void animacionFinalizada(std::string _animacionActual)=0;
		virtual void configurarAnimaciones() = 0;

	private:

		std::map<std::string, std::vector<SDL_Rect> > _animaciones;
		std::map<std::string, Vector2> _offsets;
		int _frameIndex;
		double tiempoTrancurrido;
		bool _visible;

};

#endif
