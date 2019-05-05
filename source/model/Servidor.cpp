#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <iostream>
#include <string.h>
#include <Servidor.hpp>
#include <pthread.h>
#include <stdio.h>
#include <ControladorEnvio.hpp>
using namespace std;

#define PUERTO 5001
struct infoCliente{
	Servidor *servidor;
	int id;
	int socket;
};
typedef struct infoCliente Cliente;

Servidor::Servidor(){
	this->sisEnvio=ControladorEnvio();
	this->cantidadDeClientes=0;

	int socketServidor,socketCliente,cantidadClientes;
	struct sockaddr_in servidor; // informacion de la direccion del servidor
	struct sockaddr_in cliente; // informacion de la direccion del cliente
	int tamanioCliente;
	cantidadClientes=0;


	socketServidor=socket(AF_INET,SOCK_STREAM,0);//AF_INET IPV4,SOCK_STREAM TCP
	if (socketServidor==-1){
		cout<<"error en el socket"<<endl;
	};
	servidor.sin_family=AF_INET;
	servidor.sin_port=htons(PUERTO); //definimos el puerto
	servidor.sin_addr.s_addr=INADDR_ANY;// ponemos nuestra ip


	if((bind(socketServidor,(struct sockaddr*)&servidor,sizeof(struct sockaddr)))<0){
		cout<<"error en el enlace"<<endl;
	};

	listen(socketServidor,3);
	puts("Esperando conexiones");
	tamanioCliente=sizeof(cliente);
	pthread_t thread_id;
	Cliente * infoCliente=(Cliente*)malloc(sizeof(Cliente));
	while(true){
		if(this->cantidadDeClientes<CANT_MAX_CLIENTES){
		socketCliente=accept(socketServidor,(struct sockaddr*)&cliente,(socklen_t*)&tamanioCliente);

		if(socketCliente<0){
			cout<<"error al aceptar"<<endl;
		};
		puts("conexion acceptada");
		this->cantidadDeClientes++;
		infoCliente->servidor=this;
		infoCliente->id=this->cantidadDeClientes;
		infoCliente->socket=socketCliente;
		if((pthread_create(&thread_id,NULL,Servidor::conexionCliente,(void*)infoCliente))<0){
			std::cout<<"error al creal el socket"<<endl;
		};
		cout<<"Bienvenido: "<<this->cantidadDeClientes<<endl;
		}
		else{
			std::cout<<"todo lleno"<<endl;
		}
	}
}
void Servidor::enviarIdCliente(int idCliente,int socketCliente){
	this->sisEnvio.enviarEntero(idCliente,socketCliente);
	this->sisEnvio.enviarString("Conectado",socketCliente);
}

void *Servidor::conexionCliente(void*cliente){
	Cliente* argumentos = (Cliente*) cliente;
	((Servidor*)argumentos->servidor)->enviarIdCliente(argumentos->id,argumentos->socket);
}

