#ifndef SOURCE_VIEW_PARALLAXCLIENTE_HPP_
#define SOURCE_VIEW_PARALLAXCLIENTE_HPP_

#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <vector>

class TexturasFondos {

public:
	TexturasFondos(ControladorGrafico &graficos);
	~TexturasFondos();
	void cargarFondos();
	void cargarTexturas(ControladorGrafico &graficos);

	SDL_Texture *backgroundz1();
	SDL_Texture *backgroundz2();
	SDL_Texture *backgroundz3();
	std::vector<int> getzindexes();


private:
	std::vector<std::string > fondos;
	std::vector<int > zindexs;
	SDL_Surface *background_z1 = NULL;
	SDL_Surface *background_z2 = NULL;
	SDL_Surface *background_z3 = NULL;
	SDL_Texture *bitmapTex1 = NULL ;
	SDL_Texture *bitmapTex2 = NULL;
	SDL_Texture *bitmapTex3 = NULL;



};



#endif
