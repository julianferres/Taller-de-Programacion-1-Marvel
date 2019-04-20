#include <GameMenu.hpp>
#include <ControladorGrafico.hpp>


extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

GameMenu::GameMenu(ControladorGrafico &graficos){
	TTF_Init();

	this->marvelFont = TTF_OpenFont("contents/Fonts/Marvel.ttf", 64);
	controladorLogger->registrarEvento("INFO", "Iniciando menu");
	this->crearBotones(graficos);
	this->handleEvent(graficos);
}

GameMenu::~GameMenu(){
	TTF_CloseFont(marvelFont);
	TTF_Quit();
}


void GameMenu::crearBotones(ControladorGrafico &graficos){
	for (int i = 0; i < controladorJson->cantidadPersonajes(); i++){
		this->crearBotonParaPersonaje(graficos,i);
	}
}

void GameMenu::crearBotonParaPersonaje(ControladorGrafico &graficos, int i){
	Boton botonI = Boton(graficos, 250*(i+1), 400 , 200, 200, controladorJson->nombrePersonajeI(i));
	this->botones.push_back(botonI);
}

void GameMenu::handleEvent(ControladorGrafico &graficos){//int personaje, int jugador){
	SDL_Event e;
	bool quit = false;
	int jugador=1;
	int personaje=1;
	while(!quit && (jugador <3)){
			//Elegir personaje 1 Jugador 1
		while( SDL_PollEvent( &e ) != 0 ){
			if( e.type == SDL_QUIT ){
				quit = true;
			}
			for (int i = 0; i< this->botones.size(); i++){
				//controladorLogger->registrarEvento("DEBUG", "GameMenu::handleando evento para boton " + std::to_string(i));
				this->botones[i].handleEvent(e);
				if (e.type == SDL_MOUSEBUTTONUP && this->botones[i].fueClickeado()){
					controladorJson->setPersonajeJugador(personaje, jugador, this->botones[i].Nombre());
					controladorLogger->registrarEvento("DEBUG", "GameMenu::Personaje Seteado");
					personaje++;
					controladorLogger->registrarEvento("DEBUG", "GameMenu::Sumo uno a personaje = "+ std::to_string(personaje));
					if (personaje > 2){
						personaje=1;
						jugador++;
						controladorLogger->registrarEvento("DEBUG", "GameMenu::Sumo uno a jugador = " + std::to_string(jugador));
					}
				}

			}
		this->dibujar(graficos);
		}
	}
	controladorLogger->registrarEvento("DEBUG", "GameMenu::Menu terminado");
}

void GameMenu::dibujar(ControladorGrafico &graficos){
	graficos.limpiar();

	SDL_Surface* textSurface = TTF_RenderText_Solid(marvelFont, "MARVEL", { 255, 0, 0} );
	SDL_Rect sourceRect = { 200,100, 200, 100};
	SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(graficos.getRenderer(), textSurface);
	graficos.dibujarImagen(TextTexture, &sourceRect, NULL, SDL_FLIP_NONE);

	for (int i = 0; i< this->botones.size(); i++){
		this->botones[i].dibujar(graficos);
	}
	graficos.render();
}

void GameMenu::elegirPersonajes(ControladorGrafico &graficos){
	/*SDL_Event e;
	bool quit = false;
	int jugador=1;
	int personaje=1;
	while(!quit || (personaje>2 && jugador >2)){
		//Elegir personaje 1 Jugador 1
		quit = this->handleEvent(e,personaje, jugador);
		if( e.type== SDL_MOUSEBUTTONUP){
			personaje++;
			if (personaje > 2){
				personaje=1;
				jugador=2;
			}
		}
	this->dibujar(graficos);
	}*/

}
