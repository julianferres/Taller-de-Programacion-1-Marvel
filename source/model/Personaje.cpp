#include <ControladorTexturas.h>
#include <Personaje.h>

Personaje::Personaje(const char* imagen, int x, int y){
	objTexture = ControladorTexturas::LoadTexture(imagen);
	xpos = x;
	ypos = y;

}

void Personaje::Update(){

	srcRect.h = 286;
	srcRect.w = 256;
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w ;
	destRect.h = srcRect.h;

}

void Personaje::Render(){
	SDL_RenderCopy(Juego::renderer, objTexture, &srcRect, &destRect);
}

void Personaje::MoverDerecha(){
	xpos += 30;
}

void Personaje::MoverIzquierda(){
	xpos -= 30;
}

