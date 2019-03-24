#ifndef PERSONAJE_H_
#define PERSONAJE_H_

#include <Juego.hpp>

class Personaje{

public:
	Personaje(const char* texturesheet, int x, int y);
	~Personaje();
	void Update();
	void Render();
	void MoverDerecha();
	void MoverIzquierda();

private:
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};



#endif /* PERSONAJE_H_ */

//feature/personaje

