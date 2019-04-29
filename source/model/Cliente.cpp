#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <Cliente.hpp>

using namespace std;

#define PUERTO 5001

#define MAXDATOS 256 // podemos enviar solo 100 bytes

Cliente::Cliente( char * direccionIP){
	int socket1,numeroBytes,conexion;
	char buffer[MAXDATOS];
	struct hostent *nodoServidor;
	struct sockaddr_in servidor;

	nodoServidor=gethostbyname(direccionIP); //la direccion ip que le pasamos por parametro
	if(nodoServidor==NULL){
		cout<<"error en la direccion"<<endl;
	}

	socket1=socket(AF_INET, SOCK_STREAM, 0); //lanzamos el socket

	servidor.sin_family=AF_INET; // lo mismo que el servidor
	servidor.sin_port=htons(PUERTO);
	servidor.sin_addr=*((struct in_addr *)nodoServidor->h_addr);
	bzero(&(servidor.sin_zero),8);

	conexion=connect(socket1,(struct sockaddr *)&servidor,sizeof(struct sockaddr));
	if(conexion==-1){
	cout<<"error al conectar"<<endl;
	}



	while(true){
		/* enviarEventos  send(socketCliente, evento,sizeof(evento),0);
		 * recibir vista recv(socket1,buffer,MAXDATOS,0);
		 * dibujar
		 */

	}




	close(socket1);
}
