#ifndef HEADERS_CONTROLER_CONTROLADORENVIO_HPP_
#define HEADERS_CONTROLER_CONTROLADORENVIO_HPP_
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <iostream>

using namespace std;
struct vector4{
	int x;
	int y;
	int w;
	int h;
};
typedef struct vector4 vector4Entero;

class ControladorEnvio{
	public:
		ControladorEnvio();
		void enviarEntero(int entero,int socket);
		void enviarString(string cadena,int socket);
		int recibirEntero(int socket);
		string recibirString(int socket);
		void enviarArrayEnteros(struct vector4 datos,int socket);
		struct vector4 recibirArrayEnteros(int socket);
	private:

};
#endif
