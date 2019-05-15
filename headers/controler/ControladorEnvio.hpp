#ifndef HEADERS_CONTROLER_CONTROLADORENVIO_HPP_
#define HEADERS_CONTROLER_CONTROLADORENVIO_HPP_
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

using namespace std;
struct vector8{
	int x;
	int y;
	int w;
	int h;
};
typedef struct vector8 vector8Entero;

class ControladorEnvio{
	public:
		ControladorEnvio();
		void enviarEntero(int entero,int socket);
		void enviarString(string cadena,int socket);
		int recibirEntero(int socket);
		string recibirString(int socket);
		void enviarArrayEnteros(struct vector8 datos,int socket);
		struct vector8 recibirArrayEnteros(int socket);
		void enviarEvento(SDL_Event evento,int socket);
		SDL_Event recibirEvento(int socket);

	private:

};
#endif
