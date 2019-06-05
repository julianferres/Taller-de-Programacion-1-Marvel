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


void ControladorSonido::correrCancion(const char* nombre,int repeticiones){
	//while(Mix_PlayingMusic())
		//continue;
	if(repeticiones==-1){
		Mix_Music *song = Mix_LoadMUS(nombre);
		if(Mix_PlayMusic(song, repeticiones)==-1) cout<<Mix_GetError()<<endl;
	}
	else{
		Mix_Chunk *junk = Mix_LoadWAV(nombre);
		if(!Mix_Playing(-1))
			Mix_PlayChannel(-1,junk,0);
	}

}

void ControladorSonido::detenerCancion(){
	if(Mix_PausedMusic())
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}
