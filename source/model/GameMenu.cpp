#include <GameMenu.hpp>
#include <ControladorGrafico.hpp>
#include <Boton.hpp>


extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

GameMenu::GameMenu(ControladorGrafico &graficos){
	TTF_Init();
	this->alto_ventana = controladorJson->alturaVentana();
	this->ancho_ventana = controladorJson->anchoVentana();
	this->marvelFont = TTF_OpenFont("contents/Fonts/Marvel.ttf", (300 * this->ancho_ventana) / this->ancho_maximo_ventana);
	this->selectFont = TTF_OpenFont("contents/Fonts/select.ttf", (100 * this->ancho_ventana) / this->ancho_maximo_ventana);
	this->pixelFont = TTF_OpenFont("contents/Fonts/Pixel.ttf", (50 * this->ancho_ventana) / this->ancho_maximo_ventana);
	controladorLogger->registrarEvento("INFO", "Iniciando menu");
	this->crearBotones(graficos);
	this->tituloSurface = TTF_RenderText_Solid(marvelFont, "MARVEL", { 255, 0, 0} );
	this->tituloTexture = SDL_CreateTextureFromSurface(graficos.getRenderer(), this->tituloSurface);

	this->subTituloSurface = TTF_RenderText_Solid(selectFont, "ELIJE A TUS HEROES", { 255, 252, 51} );
	this->subTituloTexture = SDL_CreateTextureFromSurface(graficos.getRenderer(), this->subTituloSurface);

	this->actionSurface = TTF_RenderText_Solid(pixelFont, "Jugador 1 elija al personaje 1", { 0, 0, 251} );
	this->actionTexture = SDL_CreateTextureFromSurface(graficos.getRenderer(), this->actionSurface);

	this->handleEvent(graficos);
}

GameMenu::~GameMenu(){
	for(int i=0;i<botones.size();i++)
		delete botones[i];
	SDL_DestroyTexture(actionTexture);
	SDL_FreeSurface(actionSurface);
	SDL_DestroyTexture(subTituloTexture);
	SDL_FreeSurface(subTituloSurface);
	SDL_DestroyTexture(tituloTexture);
	SDL_FreeSurface(tituloSurface);
	TTF_CloseFont(selectFont);
	TTF_CloseFont(marvelFont);
	TTF_Quit();
}


void GameMenu::crearBotones(ControladorGrafico &graficos){
	for (int i = 0; i < controladorJson->cantidadPersonajes(); i++){
		this->crearBotonParaPersonaje(graficos,i);
	}
}

void GameMenu::crearBotonParaPersonaje(ControladorGrafico &graficos, int i){
	Boton *boton =new Boton(graficos, ((250* this->ancho_ventana) / this->ancho_maximo_ventana)*(i+1), (400 * this->alto_ventana) / this->alto_maximo_ventana , (200 * this->ancho_ventana) / this->ancho_maximo_ventana, (200 * this->alto_ventana) / this->alto_maximo_ventana, controladorJson->nombrePersonajeI(i));
	this->botones.push_back(boton);
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
				this->botones[i]->handleEvent(e);
				if (e.type == SDL_MOUSEBUTTONUP && this->botones[i]->fueClickeado()){
					controladorJson->setPersonajeJugador(personaje, jugador, this->botones[i]->Nombre());
					controladorLogger->registrarEvento("DEBUG", "GameMenu::Personaje Seteado");					personaje++;
					controladorLogger->registrarEvento("DEBUG", "GameMenu::Sumo uno a personaje = "+ std::to_string(personaje));
					if (personaje > 2){
						personaje=1;
						jugador++;
						controladorLogger->registrarEvento("DEBUG", "GameMenu::Sumo uno a jugador = " + std::to_string(jugador));
					}
					std::string text = "Jugador " + std::to_string(jugador) + " elija al personaje " + std::to_string(personaje);
					this->actionSurface = TTF_RenderText_Solid(pixelFont, text.c_str() , { 0, 0, 251} );
					this->actionTexture = SDL_CreateTextureFromSurface(graficos.getRenderer(), this->actionSurface);

				}

			}
		this->dibujar(graficos);

		}
	}
	controladorLogger->registrarEvento("DEBUG", "GameMenu::Menu terminado");
}

void GameMenu::dibujar(ControladorGrafico &graficos){
	graficos.limpiar();
	int w =0;int h=0;
	SDL_QueryTexture(tituloTexture, NULL, NULL,&w , &h);
	SDL_Rect sourceRect = { (this->ancho_ventana -w)/2,(10 * this->alto_ventana) / this->alto_maximo_ventana,w,h};
	graficos.dibujarImagen(tituloTexture, NULL, &sourceRect, SDL_FLIP_NONE);

	for (int i = 0; i< this->botones.size(); i++){
		this->botones[i]->dibujar(graficos);
	}

	SDL_QueryTexture(subTituloTexture, NULL, NULL,&w , &h);
	sourceRect = { (this->ancho_ventana -w)/2, (270 * this->alto_ventana) / this->alto_maximo_ventana,w,h};
	graficos.dibujarImagen(subTituloTexture, NULL, &sourceRect, SDL_FLIP_NONE);



	SDL_QueryTexture(actionTexture, NULL, NULL,&w , &h);
	sourceRect = { (this->ancho_ventana -w)/2,(670 * this->alto_ventana) / this->alto_maximo_ventana,w,h};
	graficos.dibujarImagen(actionTexture, NULL, &sourceRect, SDL_FLIP_NONE);

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
