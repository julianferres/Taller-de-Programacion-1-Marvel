#ifndef HEADERS_CONTROLER_CONTROLADORENVIO_HPP_
#define HEADERS_CONTROLER_CONTROLADORENVIO_HPP_
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class ControladorEnvio{
	public:
		ControladorEnvio();
		void enviarEntero(int entero,int socket);
		void enviarString(string cadena,int socket);
		int recibirEntero(int socket);
		string recibirString(int socket);
	private:

};
#endif
