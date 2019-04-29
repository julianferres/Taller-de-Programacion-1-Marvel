/*#ifndef ESCENAINICIAL_HPP_
#define ESCENAINICIAL_HPP_

#include <vector>
#include <SDL2/SDL_image.h>
#include <string>

class EscenaInicial{

	public:
		EscenaInicial(std::vector<std::string, std::string> personajes, std::vector<std::string> filepathsFondos);
	private:
		//(nombre_personaje, filepath_personaje)
		std::vector<std::string, std::string> personajes;
		//filepath ordenados de los fondos (fondoZ0, fondoZ1, fondoZ2)
		std::vector<std::string> filepathsFondos;

};



#endif */
