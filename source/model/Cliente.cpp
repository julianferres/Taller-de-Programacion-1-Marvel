#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <string.h>
#include <Cliente.hpp>

using namespace std;

#define PUERTO 5001

#define MAXDATOS 256

Cliente::Cliente( char * direccionIP){
	int socketConexion,numeroBytes,conexion;
	struct hostent *nodoServidor;
	struct sockaddr_in servidor;

	nodoServidor=gethostbyname(direccionIP);
	if(nodoServidor==NULL){
		cout<<"error en la direccion"<<endl;
	}

	socketConexion=socket(AF_INET, SOCK_STREAM, 0);
	servidor.sin_family=AF_INET;
	servidor.sin_port=htons(PUERTO);
	servidor.sin_addr=*((struct in_addr *)nodoServidor->h_addr);
	bzero(&(servidor.sin_zero),8);

	conexion=connect(socketConexion,(struct sockaddr *)&servidor,sizeof(struct sockaddr));

	if(conexion<0){
	cout<<"error al conectar"<<endl;
	};
	//Recibir Entero
	void * buffer =malloc(4);
	recv(socketConexion,buffer,4,0);
	int cliente;
	memcpy(&cliente,buffer,4);
	std::cout<<"tengo id: "<<cliente<<endl;
	this->idCliente=cliente;

	std::cout<<"tengo guardado id: "<<this->idCliente<<endl;
	//Recibir String
	buffer=malloc(4);
	recv(socketConexion,buffer,4,0);
	int largo;
	memcpy(&largo,buffer,4);
	char bufer[largo+1];
	recv(socketConexion,bufer,largo+1,0);
	string mensaje(bufer);
	std::cout<<"mensaje: "<<mensaje<<endl;

	recv(socketConexion,bufer,largo+1,0); //esto hace que no termine el cliente

	close(socketConexion);
}
