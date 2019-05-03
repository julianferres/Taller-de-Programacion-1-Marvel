#ifndef SOURCE_MODEL_TEXTURASPERSONAJES_HPP_
#define SOURCE_MODEL_TEXTURASPERSONAJES_HPP_
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Texturas {
	public:
		Texturas(ControladorGrafico &graficos,vector<tuple<string, const string>> nombresYpaths);
		SDL_Texture * getTextura(string nombre);
	private:
		std::map<string, SDL_Texture*> texturas;
};



#endif
