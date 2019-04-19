#include <Boton.hpp>


extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

Boton::Boton(int posX, int posY, int width, int heigth){
	this->posicion.x = posX;
	this->posicion.y = posY;
	this->width = width;
	this->height = heigth;
	this->spriteActual = BOTON_SPRITE_MOUSE_OUT;
}

void Boton::setPosicion(int x, int y){
	this->posicion.x = x;
	this->posicion.y = y;
}

void Boton::handleEvent(SDL_Event* e){
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
		//Obtengo posicion del mouse
		int x, y;
		SDL_GetMouseState( &x, &y );
		//Mouse est[a dentro del boton
		bool inside = true;

		//El Mouse est[a fuera del boton
		if( x < this->posicion.x ){
			inside = false;
		}else if( x > this->posicion.x + this->width ){
			inside = false;
		}else if( y < this->posicion.y ){
			inside = false;
		}else if( y > this->posicion.y + this->height ){
			inside = false;
		}
        if( !inside ){
            this->spriteActual = BOTON_SPRITE_MOUSE_OUT;
        }

        //El mouse esta dentro del boton
        else{
            switch( e->type ){
                case SDL_MOUSEMOTION:
					this->spriteActual = BOTON_SPRITE_MOUSE_OVER_MOTION;
					break;
                case SDL_MOUSEBUTTONDOWN:
					this->spriteActual = BOTON_SPRITE_MOUSE_DOWN;
					break;
                case SDL_MOUSEBUTTONUP:
					this->spriteActual = BOTON_SPRITE_MOUSE_UP;
					break;
				}
        }
	}
}
