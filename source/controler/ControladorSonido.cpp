#include <ControladorSonido.hpp>
#include <iostream>

using namespace std;

ControladorSonido::ControladorSonido(){
	SDL_Init( SDL_INIT_AUDIO);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
	cargarGolpes("CapitanAmerica");
	cargarGolpes("Spiderman");
	cargarGolpes("MegaMan");
	cargarGolpes("Venom");
}

ControladorSonido::~ControladorSonido(){
	SDL_AudioQuit();
}


void ControladorSonido::correrSonido(const char* nombre,bool esperar){
	Mix_Chunk *junk = Mix_LoadWAV(nombre);
	if(esperar)
		while(Mix_Playing(-1)){}
	Mix_PlayChannel(-1,junk,0);

}

void ControladorSonido::correrCancionFondo(const char* nombre,int repeticiones){
	if(Mix_PlayingMusic())
		return;

	Mix_Music *song = Mix_LoadMUS(nombre);
	if(Mix_PlayMusic(song, repeticiones)==-1) cout<<Mix_GetError()<<endl;
}

void ControladorSonido::detenerCancion(){
	if(Mix_PausedMusic())
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}

void ControladorSonido::finalizarCancion(){
	Mix_HaltMusic();
}



void ControladorSonido::cargarGolpes(string personaje){
	sonidos[make_tuple(personaje,"golpeF")]=string("contents/sounds/") + personaje + string("/golpeF.wav");
	sonidos[make_tuple(personaje,"golpeS")]=string("contents/sounds/")+personaje+ string("/golpeS.wav");
	sonidos[make_tuple(personaje,"patadaF")]=string("contents/sounds/") + personaje + string("/golpeF.wav");
	sonidos[make_tuple(personaje,"patadaS")]=string("contents/sounds/")+personaje+ string("/golpeS.wav");
	sonidos[make_tuple(personaje,"recibirDanio")] =string("contents/sounds/")+personaje+ string("/recibirDanio.wav");
	sonidos[make_tuple(personaje,"cambioEntrada")] = string("contents/sounds/")+personaje+ string("/cambio.wav");
	sonidos[make_tuple(personaje,"disparar")] = string("contents/sounds/")+personaje+ string("/disparo.wav");
	sonidos[make_tuple(personaje,"muerte")] = string("contents/sounds/")+personaje+ string("/muerte.wav");

}

string ControladorSonido::getSonidoAnimacion(string personaje,string golpe){
	return sonidos[make_tuple(personaje,golpe)];
}
