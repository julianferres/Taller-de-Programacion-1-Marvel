#ifndef HEADERS_MODEL_GAMEMENU_HPP_
#define HEADERS_MODEL_GAMEMENU_HPP_
#include <Boton.hpp>
#include <vector>

class GameMenu{
public:
	GameMenu(ControladorGrafico &graficos);
	~GameMenu();
	void crearBotones(ControladorGrafico &graficos);
	void crearBotonParaPersonaje(ControladorGrafico &graficos, int i);
private:
	std::vector<Boton> botones;
};



#endif /* HEADERS_MODEL_GAMEMENU_HPP_ */
