#include <GameMenu.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

GameMenu::GameMenu(){
	controladorLogger->registrarEvento("INFO", "Iniciando menu");
	this->crearBotones();
}



void GameMenu::crearBotones(){
	for (int i = 0; i < controladorJson->cantidadPersonajes(); i++){
		this->crearBotonParaPersonaje(i);
	}
}

void GameMenu::crearBotonParaPersonaje(int i){
	Boton botonI = Boton(100, 120*(i+1), 100, 100);
}
