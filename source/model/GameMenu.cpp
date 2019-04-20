#include <GameMenu.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

GameMenu::GameMenu(ControladorGrafico &graficos){
	controladorLogger->registrarEvento("INFO", "Iniciando menu");
	this->crearBotones(graficos);
}



void GameMenu::crearBotones(ControladorGrafico &graficos){
	for (int i = 0; i < controladorJson->cantidadPersonajes(); i++){
		this->crearBotonParaPersonaje(graficos,i);
	}
}

void GameMenu::crearBotonParaPersonaje(ControladorGrafico &graficos, int i){
	Boton botonI = Boton(graficos, 100, 120*(i+1), 100, 100, controladorJson->nombrePersonajeI(i));
}
