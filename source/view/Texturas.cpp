#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <map>
#include <tuple>
#include <SpriteAnimado.hpp>
#include <Texturas.hpp>

using namespace std;

Texturas::Texturas(ControladorGrafico &graficos,vector<tuple<string, const string>> nombresYpaths){
	for(int i=0;i<nombresYpaths.size();i++){
		tuple<string,const string> tuplai = nombresYpaths[i];
		const string &filePath = get<1>(tuplai);
		string nombre = get<0>(tuplai);
		 SDL_Texture *t1 =SDL_CreateTextureFromSurface(graficos.getRenderer(),graficos.cargarImagen(filePath));
		 texturas[nombre] = t1;
	}

}

SDL_Texture * Texturas::getTextura(string nombre){
	return this->texturas[nombre];
}

