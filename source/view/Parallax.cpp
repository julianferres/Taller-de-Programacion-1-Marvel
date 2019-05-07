#include <Parallax.hpp>
#include <SDL2/SDL.h>
#include <ControladorGrafico.hpp>
#include <ControladorJson.hpp>
#include <ControladorLogger.hpp>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;


Parallax::Parallax(){
	std::vector<std::string > fondos;
	for(int i=0; i<99; i++){
		std::string fondo = controladorJson->pathFondo(i);
		if(!fondo.empty() ){
			fondos.push_back(fondo);
		}
	}
	SDL_Surface *background_z1 = IMG_Load(fondos[0].c_str());
	SDL_Surface *background_z2 = IMG_Load(fondos[1].c_str());
	SDL_Surface *background_z3 = IMG_Load(fondos[2].c_str());
	fondo1_w = background_z1->w;
	fondo2_w = background_z2->w;
	fondo3_w = background_z3->w;

	this->iniciarCamaras();

}

Parallax::~Parallax(){

}


void Parallax::iniciarCamaras(){

		camera_z1.x = fondo1_w/2 - W/2;
		camera_z1.y = 0;
		camera_z1.w = W;
		camera_z1.h = H;
		controladorLogger->registrarEvento("DEBUG", "Parallax::Camara 1 inicializada");


		camera_z2.x = fondo2_w/2 -W/2;
		camera_z2.y = 0;
		camera_z2.w = W;
		camera_z2.h = H;
		controladorLogger->registrarEvento("DEBUG", "Parallax::Camara 2 inicializada");


		camera_z3.x = fondo3_w/2 - W/2;
		camera_z3.y = 0;
		camera_z3.w = W;
		camera_z3.h = H;
		controladorLogger->registrarEvento("DEBUG", "Parallax::Camara 3 inicializada");

}

void Parallax::moverCamaraDerecha(){
	if(finDeEscenarioDerecha() ){
		return;
	}

		camera_z1.x += SPEED_z1;

		camera_z2.x += SPEED_z2;

		camera_z3.x += SPEED_z3;

}


void Parallax::moverCamaraIzquierda(){
	if(finDeEscenarioIzquierda()){
		return;
	}

		camera_z1.x -= SPEED_z1;


		camera_z2.x -= SPEED_z2;


		camera_z3.x -= SPEED_z3;

}

bool Parallax::finDeEscenarioIzquierda(){
	bool finEscenario = false;

		finEscenario = finEscenario || camera_z1.x <= 0;


		finEscenario = finEscenario || camera_z2.x <= 0;


		finEscenario = finEscenario || camera_z3.x <= 0;

	return finEscenario;//camera_z1.x <= 0 || camera_z2.x <= 0 || camera_z3.x <= 0;
}

bool Parallax::finDeEscenarioDerecha(){
	bool finEscenario = false;

	finEscenario = finEscenario || camera_z1.x >= fondo1_w - W;


	finEscenario = finEscenario || camera_z2.x >= fondo2_w - W ;


	finEscenario = finEscenario || camera_z3.x >= fondo3_w - W;

	return finEscenario;
}


SDL_Rect *Parallax::camaraz1(){
	return &camera_z1;
}

SDL_Rect *Parallax::camaraz2(){
	return &camera_z2;
}

SDL_Rect *Parallax::camaraz3(){
	return &camera_z3;
}



