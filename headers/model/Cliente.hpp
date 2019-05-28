#ifndef HEADERS_MODEL_CLIENTE_HPP_
#define HEADERS_MODEL_CLIENTE_HPP_
#include <GameMenu.hpp>
#include <JuegoCliente.hpp>
#include <ControladorLogger.hpp>
#include <ControladorEnvio.hpp>
#include <string>
#include <tuple>
#include <SDL2/SDL_image.h>

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
		void partidallena();
		int verificarConexion(int recibido);

	private:
		JuegoCliente *juegoCliente;
		ControladorEnvio sistemaEnvio;
		int idCliente;
		int numeroSocket;
		char buffer[MAXDATOS];
		bool running = true;
		bool enMenu = true;
		vector<tuple<string, const string>> personajesYfondos;
		bool conectado=true;

	};

#endif
