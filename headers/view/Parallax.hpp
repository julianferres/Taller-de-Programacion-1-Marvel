#ifndef parallax_hpp
#define parallax_hpp

#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <vector>

extern ControladorJson *controladorJson;

class Parallax{

	public:

		~Parallax();
		Parallax(ControladorGrafico &graficos);
		void moverCamaraIzquierda();
		void moverCamaraDerecha();
		void cargarFondos();
		void cargarTexturas(ControladorGrafico &graficos);
		void iniciarCamaras();
		bool finDeEscenarioDerecha();
		bool finDeEscenarioIzquierda();

		SDL_Rect *camaraz1();
		SDL_Rect *camaraz2();
		SDL_Rect *camaraz3();
		SDL_Texture *backgroundz1();
		SDL_Texture *backgroundz2();
		SDL_Texture *backgroundz3();
		std::vector<int> getzindexes();

	private:

		int W = controladorJson->anchoVentana();
		int H = controladorJson->alturaVentana();
		const int SPEED_z1 = 5;
		const int SPEED_z2=  7.5;
		const int SPEED_z3 = 10;
		SDL_Rect camera_z1;
		SDL_Rect camera_z2;
		SDL_Rect camera_z3;
		SDL_Surface *background_z1 = NULL;
		SDL_Surface *background_z2 = NULL;
		SDL_Surface *background_z3 = NULL;
		SDL_Texture *bitmapTex1 = NULL ;
		SDL_Texture *bitmapTex2 = NULL;
		SDL_Texture *bitmapTex3 = NULL;
		std::vector<std::string > fondos;
		std::vector<int > zindexs;

};

#endif


