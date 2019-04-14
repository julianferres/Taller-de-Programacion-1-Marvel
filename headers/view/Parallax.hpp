#ifndef parallax_hpp
#define parallax_hpp

#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <vector>

extern ControladorJson *controladorJson;

class Parallax{

	public:

		SDL_Rect camera_z1;
		SDL_Rect camera_z2;
		SDL_Rect camera_z3;
		SDL_Surface *background_z1 = NULL;
		SDL_Surface *background_z2 = NULL;
		SDL_Surface *background_z3 = NULL;
		std::vector<std::string > fondos;
		std::vector<int > zindexs;
		SDL_Texture *bitmapTex1 = NULL ;
		SDL_Texture *bitmapTex2 = NULL;
		SDL_Texture *bitmapTex3 = NULL;

		void MoverCamaraIzquierda();
		void MoverCamaraDerecha();
		void cargarFondos();
		void cargarTexturas(ControladorGrafico &graficos);
		void iniciarCamaras();

		SDL_Rect *Camaraz1();
		SDL_Rect *Camaraz2();
		SDL_Rect *Camaraz3();
		SDL_Texture *Backgroundz1();
		SDL_Texture *Backgroundz2();
		SDL_Texture *Backgroundz3();

		bool finDeEscenarioDerecha();
		bool finDeEscenarioIzquierda();

		Parallax();
		~Parallax();
		Parallax(ControladorGrafico &graficos);

	private:

		int W = controladorJson->anchoVentana();
		int H = controladorJson->alturaVentana();
		const int SPEED_z1 = 5;
		const int SPEED_z2=  7.5;
		const int SPEED_z3 = 10;

};
#endif


