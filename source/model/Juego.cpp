//#include <ControladorTexturas.h>
#include <Juego.hpp>
#include <ControladorGrafico.hpp>
#include <Personaje.hpp>
#include <ControladorTeclado.hpp>

Personaje _jugador1 ;
Personaje _jugador2;
ControladorTeclado input;
//SDL_Renderer* Juego::renderer = nullptr;
namespace{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}
Juego::Juego(){
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();

}

Juego::~Juego()
{}

void Juego::gameLoop(){
	ControladorGrafico graficos;


	this->iniciarJugadores(graficos);
	int flags = 0;

	if(this->_fullScreen){
		flags = SDL_WINDOW_FULLSCREEN;
	}
	int LAST_UPDATE_TIME = SDL_GetTicks();
	while(this->isRunning){
		input.empezarNuevoFrame();
		this->atraparEventos();

		if (input.sePresionoUnaTecla(SDL_SCANCODE_ESCAPE) == true){
				return;
			}
		//Controles Jugador 1
		else if(input.seEstaPresionandoUnaTecla(SDL_SCANCODE_LEFT) == true){
			_jugador1.MoverIzquierda();
		}
		else if(input.seEstaPresionandoUnaTecla(SDL_SCANCODE_RIGHT) == true){
			_jugador1.MoverDerecha();
		}
		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->dibujar(graficos);
	}
}



void Juego::iniciarJugadores(ControladorGrafico &graficos){
	_jugador1 = Personaje(graficos, 100, 100);
	//this->_jugador2 = Personaje(graficos, 100, 100);
}

/*	ControladorGrafico graficos;
	int flags = 0;

	if(fullscreen){
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if(SDL_Init(SDL_INIT_EVERYTHING)==0){

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window,-1,0);
		if(renderer){
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
		std::cout << "Juego iniciado!" << std::endl;
	}
	else{
		isRunning = false;
	}


	jugador1 = new Personaje(graficos,0,300);
	jugador2 = new Personaje(graficos,500,300);


}*/

void Juego::atraparEventos()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if(event.key.repeat == 0){
					input.eventoPresionarTecla(event);
				}
				break;
			case SDL_KEYUP:
				if(event.key.repeat == 0){
					input.eventoSoltarTecla(event);
					}
				break;
			default:
				break;

		}
	}

}
/*switch(event.key.keysym.sym){
	case SDLK_s:
		std::cout << "Me agacho!" << std::endl;
		break;
	case SDLK_w:
			std::cout << "Salto!" << std::endl;
			break;
	case SDLK_d:
			std::cout << "Jugador 1 a la derecha!" << std::endl;
			jugador1->MoverDerecha();
			break;
	case SDLK_a:
			std::cout << "Jugador 1 a la izquierda!" << std::endl;
			jugador1->MoverIzquierda();
			break;
	case SDLK_LEFT:
			std::cout << "Jugador 2 a la izquierda!" << std::endl;
			jugador2->MoverIzquierda();
			break;
}
break;
default:
break;*/

void Juego::update(float tiempoTranscurrido)
{
	_jugador1.update(tiempoTranscurrido);
	_jugador2.update(tiempoTranscurrido);
}

void Juego::dibujar(ControladorGrafico &graficos)
{
	graficos.clear();
	//SDL_RenderClear(renderer);
	_jugador1.dibujar(graficos);
	//_jugador2->dibujar(graficos);
	//SDL_RenderPresent(renderer);
	graficos.render();
}

/*void Juego::clean()
{
	//SDL_DestroyWindow(window);
	//SDL_DestroyRenderer(renderer);
	//SDL_Quit();
	std::cout << "Juego finalizado!" << std::endl;
}*/
//testPersonaje




