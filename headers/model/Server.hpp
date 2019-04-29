#ifndef HEADERS_MODEL_SERVER_HPP_
#define HEADERS_MODEL_SERVER_HPP_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>

class Server{


public:
	Server();
	static void* connection_handler(void *socket_desc);

};



#endif
