#ifndef HEADERS_MODEL_CLIENTE_HPP_
#define HEADERS_MODEL_CLIENTE_HPP_

#include <GameMenu.hpp>
#include <JuegoCliente.hpp>
#include <ControladorLogger.hpp>
#include <ControladorEnvio.hpp>
#include <string>
#include <tuple>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <tuple>

#define MAXDATOS 1000
#define CANTIDAD_MAXIMA_JUGADORES 4

class JuegoCliente;

class Cliente{

	public:
		Cliente(char * direccionIP,int puerto);
		void iniciarConexion(char * direccionIP,int puerto);
		void cargarContenidos();
		void recibirIDcliente();
		void recibirParaDibujar();
		void elegirPersonaje();
		void enviarEventos(int socket);
		void recibirPersonajes();
		void recibirFondos();
		void recibirTitulos();
		static void* enviarEventosWrapper(void* arg);
		static void* sonidosWrapper(void* arg);
		void manejarSonidos();
		void partidallena();

	private:
		JuegoCliente *juegoCliente;
		ControladorEnvio sistemaEnvio;
		int idCliente,numeroSocket;
		char buffer[MAXDATOS];
		bool running = true;
		bool enMenu = true;
		bool conectado = true;
		vector<tuple<string, const string>> personajesYfondos;


	};

#endif
