#ifndef HEADERS_MODEL_SERVIDOR_HPP_
#define HEADERS_MODEL_SERVIDOR_HPP_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include <Juego.hpp>
#include <ControladorLogger.hpp>
#include <ControladorEnvio.hpp>
#include <queue>

using namespace std;

#define CANTIDAD_MAXIMA_JUGADORES 2
#define MAXDATOS 1000

class Servidor{

	public:
		Servidor(int puerto);
		void crearSocket(int puerto);
		void esperarConexiones();
		void enviarParaDibujar(int csocket);
		static void*enviarParaDibujarWrapper(void *args);
		static void*recibirTeclasWrapper(void *args);
		void recibirTeclas(int csocket);
		void* actualizarModelo();
		static void*actualizarModeloWrapper(void *args);
		void crearThreadServer();


	private:
		ControladorEnvio sistemaEnvio;
		Juego *juego ;
		int cantidad_actual_clientes = 0;
		int socketServidor;
		int socketCliente;
		vector<char*> vectorPersonajes;
		struct sockaddr_in server , client;
		vector<int> clientesConectados;
		vector<tuple<string,SDL_Rect , SDL_Rect ,SDL_RendererFlip>> dibujables;
		bool esperandoParaDibujar=true;
		queue<vector<tuple<string,SDL_Rect , SDL_Rect ,SDL_RendererFlip>>> dibujablesCliente1;

};


#endif
