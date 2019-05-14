#ifndef HEADERS_MODEL_SERVER_HPP_
#define HEADERS_MODEL_SERVER_HPP_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include <Juego.hpp>
#include <ControladorLogger.hpp>

using namespace std;

#define CANTIDAD_MAXIMA_JUGADORES 4
#define MAXDATOS 1000
#define PUERTO 5001


class Server{


public:
	Server();
	void crearSocket();
	void esperarConexiones();
	void* enviarParaDibujar(void *socket_desc);
	static void*enviarParaDibujarWrapper(void *args);
	static void*recibirTeclasWrapper(void *args);
	void* recibirTeclas(void* socket);
	void* actualizarModelo();
	static void*actualizarModeloWrapper(void *args);
	void crearThreadServer();


private:
	Juego *juego ;
	int cantidad_actual_clientes =0;
	int socketServidor;
	int socketCliente;
	vector<char*> vectorPersonajes;
	struct sockaddr_in server , client;
	vector<int> clientesConectados;
	vector<tuple<string,SDL_Rect , SDL_Rect >> dibujables;
	bool esperandoParaDibujar=true;



};



#endif
