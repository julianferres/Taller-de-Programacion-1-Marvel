#ifndef HEADERS_MODEL_CLIENTE_HPP_
#define HEADERS_MODEL_CLIENTE_HPP_
#include <GameMenu.hpp>
#include <JuegoCliente.hpp>
#include <ControladorLogger.hpp>
#include <ControladorEnvio.hpp>
#include <string>
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
		static void* enviarEventosWrapper(void* arg);

	private:
		JuegoCliente *juegoCliente;
		ControladorEnvio sistemaEnvio;
		int idCliente;
		int numeroSocket;
		char buffer[MAXDATOS];
		bool running = true;
		vector<tuple<string, const string>> personajesYfondos;

	};

#endif
