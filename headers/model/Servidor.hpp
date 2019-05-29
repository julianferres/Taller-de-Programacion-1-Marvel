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
#include <GameMenu.hpp>
#include <queue>
#include <mutex>

using namespace std;

#define MAXDATOS 1000

class Servidor{

	public:
		Servidor(int puerto);
		void crearSocket(int puerto);
		void esperarConexiones();
		void enviarParaDibujar(int csocket);
		static void* enviarWrapper(void* args);
		void enviarTitulos(int csocket);
		static void*recibirTeclasWrapper(void *args);
		void recibirTeclas(int csocket);
		void* actualizarModelo();
		static void*actualizarModeloWrapper(void *args);
		void crearThreadServer();
		void esperarClientes();
		void correrMenu();
		void crearEquipos();
		void gameLoop();

	private:
		mutex mutex_conecciones;
		ControladorEnvio sistemaEnvio;
		Juego *juego ;
		GameMenu *menu;
		int socketServidor;
		int socketCliente;
		int cantidadClientesPermitidos;
		vector<char*> vectorPersonajes;
		vector<int> clientesConectados;
		vector<int> clientesDesconectados;
		struct sockaddr_in server , client;
		map<int,bool> conectados;
		map<int,int> mapaIDClientes;
		vector<tuple<string,SDL_Rect , SDL_Rect ,SDL_RendererFlip>> dibujables;
		bool enMenu = true;
		queue<tuple<SDL_Event,int>>colaEventos;

};


#endif
