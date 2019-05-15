#ifndef HEADERS_MODEL_CLIENTE_HPP_
#define HEADERS_MODEL_CLIENTE_HPP_
#include <GameMenu.hpp>
#include <JuegoCliente.hpp>
#include <ControladorLogger.hpp>
#include <ControladorEnvio.hpp>
#include <string>
#include <tuple>

#define PUERTO 5001
#define MAXDATOS 1000
#define CANTIDAD_MAXIMA_JUGADORES 4

class JuegoCliente;

class Cliente{

	public:
		Cliente(char * direccionIP);
		void iniciarConexion(char * direccionIP);
		void cargarContenidos();
		void recibirIDcliente();
		void recibirParaDibujar();
		void elegirPersonaje();
		void enviarEvento();
		void recibirPersonajes();
		void recibirFondos();
		static void* enviarEventos(void* arg);

	private:
		JuegoCliente *juegoCliente;
		ControladorEnvio sistemaEnvio;
		int idCliente;
		int numeroSocket;
		char buffer[MAXDATOS];
		vector<tuple<string, const string>> personajesYfondos;

	};

#endif
