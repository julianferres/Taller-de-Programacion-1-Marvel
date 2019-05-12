#ifndef HEADERS_MODEL_SERVIDOR_HPP_
#define HEADERS_MODEL_SERVIDOR_HPP_


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <ControladorEnvio.hpp>
#include <ControladorJson.hpp>

#define CANT_MAX_CLIENTES 2
extern ControladorJson *controladorJson;
class Servidor{

	public:
		Servidor();
		void enviarInfoCliente(int idCliente,int socketCliente);
		static void *conexionCliente(void *cliente);
		void crearSocket();
		void esperarConexiones();
	private:
		int cantidadDeClientes,socketServidor,socketCliente;
		ControladorEnvio sisEnvio;
		struct sockaddr_in servidor,cliente;
};
#endif
