#ifndef parallax_hpp
#define parallax_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>


class Parallax{


public:
	Parallax();
	~Parallax();

	/*void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen );
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() {return isRunning;}
*/

	static SDL_Renderer *renderer;
	static SDL_Event event;

private:
	SDL_Window* window;
	bool collision(SDL_Rect* rect1,SDL_Rect* rect2);
	bool running;
	const int FPS =30;
	const int SPEED = 5;
	Uint32 start;
	SDL_Rect imgloc;
	SDL_Rect camera;
	bool b[2];

};

#endif
