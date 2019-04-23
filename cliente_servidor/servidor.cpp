#include <stdio.h>          
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <iostream>
#include <string.h>

using namespace std;

#define PUERTO 5001
#define CANTIDADDECONEXIONES 5

int main(){
	int socket1,socket2,enlace;
	struct sockaddr_in servidor; // informacion de la direccion del servidor
	struct sockaddr_in cliente; // informacion de la direccion del cliente
	unsigned int tamanioCliente;


	socket1=socket(AF_INET,SOCK_STREAM,0);//AF_INET IPV4,SOCK_STREAM TCP
	if (socket1==-1){
		cout<<"error en el socket"<<endl;
		return -1;
	};
	servidor.sin_family=AF_INET;
	servidor.sin_port=htons(PUERTO); //definimos el puerto
	servidor.sin_addr.s_addr=INADDR_ANY;// ponemos nuestra ip
	bzero(&(servidor.sin_zero),8); // una cadena de ceros
	
	enlace=bind(socket1,(struct sockaddr*)&servidor,sizeof(struct sockaddr));
	if(enlace==-1){
		cout<<"error en el enlace"<<endl;
		return -1;
	};
	listen(socket1,CANTIDADDECONEXIONES);
	while(true){
		tamanioCliente=sizeof(cliente);
		socket2=accept(socket1,(struct sockaddr*)&cliente,&tamanioCliente);
		if(socket2==-1){
			cout<<"error al aceptar"<<endl;
		};
		cout<<"se conecto alguien"<<endl;
		char mensaje[256];
		//unsigned long int tamanio;
		while(mensaje!="salir"){
			cin>>mensaje;
			//tamanio=sizeof(mensaje);
			send(socket2,mensaje,256,0);
		}
		close(socket2);
	}
}

