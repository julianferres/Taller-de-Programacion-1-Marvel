#include <GameMenu.hpp>
#include <ControladorGrafico.hpp>
#include <Boton.hpp>
#include <iostream>

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;
using namespace std;


GameMenu::GameMenu(){
	controladorLogger->registrarEvento("DEBUG", "GameMenu::Inicio menu");
	this->alto_ventana = controladorJson->alturaVentana();
	this->ancho_ventana = controladorJson->anchoVentana();
	this->crearBotones();

}

vector<tuple<string,string,int,string,int ,int ,int >> GameMenu::getTitulos(int csocket){
	vector<tuple<string,string,int,string,int ,int ,int >>titulos;
	string nombre1 = string("Titulo");
	string path1="contents/Fonts/Marvel.ttf";
	int size1 = (300 * this->ancho_ventana) / this->ancho_maximo_ventana;
	string descripcion1 = "MARVEL";
	SDL_Color color1 = { 255, 0, 0} ;
	tuple<string,string,int,string,int ,int ,int > marvel=make_tuple(nombre1,path1,size1,descripcion1,color1.r,color1.g,color1.b);
	titulos.push_back(marvel);

	string nombre2 = string("SubTitulo");
	string path2="contents/Fonts/select.ttf";
	int size2 = (100 * this->ancho_ventana) / this->ancho_maximo_ventana;
	string descripcion2 = "ELIJE A TUS HEROES";
	SDL_Color color2 = { 255, 252, 51};
	tuple<string,string,int,string,int ,int ,int > subtitulo=make_tuple(nombre2,path2,size2,descripcion2,color2.r,color2.g,color2.b);
	titulos.push_back(subtitulo);

	string nombre3 = string("Eleccion");
	string path3="contents/Fonts/Pixel.ttf";
	int size3 = (50 * this->ancho_ventana) / this->ancho_maximo_ventana;
	string descripcion3 = "Jugador "+ to_string(csocket)+" elija al personaje ";
	SDL_Color color3 = { 0, 0, 251};
	tuple<string,string,int,string,int ,int ,int > eleccion=make_tuple(nombre3,path3,size3,descripcion3.c_str(),color3.r,color3.g,color3.b);
	titulos.push_back(eleccion);

	return titulos;

}

GameMenu::~GameMenu(){
	for(size_t i=0;i<botones.size();i++)
		delete botones[i];
	/*SDL_DestroyTexture(actionTexture);
	SDL_FreeSurface(actionSurface);
	SDL_DestroyTexture(subTituloTexture);
	SDL_FreeSurface(subTituloSurface);
	SDL_DestroyTexture(tituloTexture);
	SDL_FreeSurface(tituloSurface);
	TTF_CloseFont(selectFont);
	TTF_CloseFont(marvelFont);
	TTF_Quit();*/
}


void GameMenu::crearBotones(){
	for (int i = 0; i < controladorJson->cantidadPersonajes(); i++){
		this->crearBotonParaPersonaje(i);
	}
}

void GameMenu::crearBotonParaPersonaje(int i){
	Boton *boton =new Boton(((250* this->ancho_ventana) / this->ancho_maximo_ventana)*(i+1), (400 * this->alto_ventana) / this->alto_maximo_ventana , (200 * this->ancho_ventana) / this->ancho_maximo_ventana, (200 * this->alto_ventana) / this->alto_maximo_ventana, controladorJson->nombrePersonajeI(i)+"Boton");
	this->botones.push_back(boton);
}

void GameMenu::handleEvent(SDL_Event e,int idCliente){
	if(clientesYaEligieron[idCliente])
		return;
	for (size_t i = 0; i< this->botones.size(); i++){
		this->botones[i]->handleEvent(e);
		if (e.type == SDL_MOUSEBUTTONUP && this->botones[i]->fueClickeado()){
			controladorLogger->registrarEvento("DEBUG", "GameMenu::Personaje "+this->botones[i]->Nombre()+" Seteado");
			string nombrePersonaje = this->botones[i]->Nombre();
			personajesElegidos[idCliente]=nombrePersonaje.substr(0,nombrePersonaje.size()-5);
			clientesYaEligieron[idCliente]=true;
		}
	}
}

map<int, string> GameMenu::getPersonajesElegidos(){
	return personajesElegidos;
}


vector<tuple<string,SDL_Rect, SDL_Rect ,SDL_RendererFlip >> GameMenu::getDibujables(){
	vector<tuple<string,SDL_Rect, SDL_Rect ,SDL_RendererFlip >> dibujables;

	SDL_Rect origen = {-1,-1,-1,-1};
	SDL_Rect destino = { this->ancho_ventana/2,(10 * this->alto_ventana) / this->alto_maximo_ventana,0,0};
	dibujables.push_back(make_tuple(string("Titulo"),origen,destino,SDL_FLIP_NONE));


	for (size_t i = 0; i< this->botones.size(); i++){
		dibujables.push_back(this->botones[i]->getDibujable() );
	}

	destino = { this->ancho_ventana /2, (270 * this->alto_ventana) / this->alto_maximo_ventana,0,0};
	dibujables.push_back(make_tuple(string("SubTitulo"),origen,destino,SDL_FLIP_NONE));

	destino = { this->ancho_ventana /2,(670 * this->alto_ventana) / this->alto_maximo_ventana,0,0};
	dibujables.push_back(make_tuple(string("Eleccion"),origen,destino,SDL_FLIP_NONE));

	return dibujables;
}


bool GameMenu::finalizado(){
	return personajesElegidos.size()==controladorJson->cantidadClientes();
}


