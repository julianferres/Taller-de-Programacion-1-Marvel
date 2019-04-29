#ifndef ESCENAINICIAL_HPP_
#define ESCENAINICIAL_HPP_

#include <vector>
#include <SDL2/SDL_image.h>
#include <string>

class EscenaInicial{

	public:
		EscenaInicial(std::vector<std::tuple<std::string, std::string>> escena);
	private:
		//(nombre, filepath)
		std::vector<std::tuple<std::string, std::string>> escena;


};


#endif
