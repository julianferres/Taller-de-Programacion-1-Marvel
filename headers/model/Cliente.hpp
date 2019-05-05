#ifndef HEADERS_MODEL_CLIENTE_HPP_
#define HEADERS_MODEL_CLIENTE_HPP_
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <string.h>
#include <ControladorEnvio.hpp>
class Cliente{

	public:
		Cliente(char * direccionIP);
	private:
		int idCliente;
		ControladorEnvio sisEnvio;

};
#endif
