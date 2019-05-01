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

using namespace std;
typedef void * (*THREADFUNCPTR)(void *);


class Server{


public:
	Server();
	void* connection_handler(void *socket_desc);
	static void*connection_handler_wrapper(void *args);

private:
	Juego *juego ;
	int cantidad_actual_clientes;
	vector<tuple<string, const string>> personajes;
};



#endif
