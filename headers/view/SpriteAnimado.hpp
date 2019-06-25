#ifndef SPRITEANIMADO_HPP_
#define SPRITEANIMADO_HPP_

#include <string>
#include <vector>
#include <Animacion.hpp>
#include <ControladorSonido.hpp>

using namespace std;

class ControladorGrafico;
class Animacion;

class SpriteAnimado{

	public:

		~SpriteAnimado();
		SpriteAnimado(string nombre);
		bool iniciarAnimacion(string animacion);
		void update();
		void cambiarAnimacion(string animacion);
		void agregarAnimacion(int frames, int x, int y, string nombre, int ancho, int alto);
		void cargarAnimaciones(string nombre);
		int getFrameIndex();
		string getAnimacionActual();
		string getNombre();
		SDL_Rect rectOrigen();
		int getAlto();
		int getAncho();
		string getSonido();


	private:

		Animacion *animacionActual;
		Animacion *serLanzado, * quieto,*moverDerecha,*moverIzquierda,*salto,*agacharse,
		*cambioEntrada,*golpeS,*patadaS,*patadaA,*golpeSaltando,*patadaSaltando,*golpeF,
		*patadaF,*golpeA,*defensa,*disparo,*tiro,*rgolpe,*rgolpeF,*levantarse,*festejo;
		Animacion * mouseOut,*mouseOver,*mouseDown,*mouseUp,*patadaSaltandoF, *golpeSaltandoF;
		Animacion *arrojable;
		vector<Animacion*> animaciones;
		int frameIndex = 0;
		int regulador = 0;
		string nombreSprite;
		bool sonidoEnviado=false;
		bool boton =true;

};

#endif
