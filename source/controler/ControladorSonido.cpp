#include <ControladorSonido.hpp>
#include <iostream>

using namespace std;

ControladorSonido::ControladorSonido(){
	SDL_Init( SDL_INIT_AUDIO);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
}

ControladorSonido::~ControladorSonido(){
	SDL_AudioQuit();
}


void ControladorSonido::correrSonido(const char* nombre){
	Mix_Chunk *junk = Mix_LoadWAV(nombre);
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
