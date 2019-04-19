#ifndef HEADERS_MODEL_GAMEMENU_HPP_
#define HEADERS_MODEL_GAMEMENU_HPP_
#include <Boton.hpp>
#include <vector>

class GameMenu{
public:
	GameMenu();
	~GameMenu();
	void crearBotones();
	void crearBotonParaPersonaje(int i);
private:
	std::vector<Boton> botones;
};



#endif /* HEADERS_MODEL_GAMEMENU_HPP_ */
