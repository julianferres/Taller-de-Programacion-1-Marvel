/*#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h> 
#include <strings.h>
#include <iostream>

using namespace std;

#define PUERTO 5001

#define MAXDATOS 256 // podemos enviar solo 100 bytes

int main(int argc, char * argv []){
	int socket1,numeroBytes,conexion;
	char buffer[MAXDATOS];
	struct hostent *nodoServidor;
	struct sockaddr_in servidor;

	nodoServidor=gethostbyname(argv[1]); //la direccion ip que le pasamos por parametro
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
	return -1;
	}
	while(true){
		numeroBytes=recv(socket1,buffer,MAXDATOS,0);
		if(numeroBytes==-1){
			cout<<"error al recibir datos"<<endl;
		}
		buffer[numeroBytes]='\0';
		cout<<"mensaje: "<<buffer<<endl;
	}
	close(socket1);
}
*/
