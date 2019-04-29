#ifndef parallax_hpp
#define parallax_hpp

#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <vector>

extern ControladorJson *controladorJson;

class Parallax{

	public:

		~Parallax();
		Parallax();
		void moverCamaraIzquierda();
		void moverCamaraDerecha();
		void iniciarCamaras();
		bool finDeEscenarioDerecha();
		bool finDeEscenarioIzquierda();
		SDL_Rect *camaraz1();
		SDL_Rect *camaraz2();
		SDL_Rect *camaraz3();



	private:

		int W = controladorJson->anchoVentana();
		int H = controladorJson->alturaVentana();
		const int SPEED_z1 = 5;
		const int SPEED_z2=  7.5;
		const int SPEED_z3 = 10;
		int fondo1_w;
		int fondo2_w;
		int fondo3_w;
		SDL_Rect camera_z1;
		SDL_Rect camera_z2;
		SDL_Rect camera_z3;


};

#endif


