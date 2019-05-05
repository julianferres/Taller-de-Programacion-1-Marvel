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
	this->crearSocket();
	this->esperarConexiones();

}
void Servidor::crearSocket(){
	this->socketServidor=socket(AF_INET,SOCK_STREAM,0);//AF_INET IPV4,SOCK_STREAM TCP
	if (this->socketServidor==-1){
		cout<<"error en el socket"<<endl;
	};
	this->servidor.sin_family=AF_INET;
	this->servidor.sin_port=htons(PUERTO); //definimos el puerto
	this->servidor.sin_addr.s_addr=INADDR_ANY;// ponemos nuestra ip


	if((bind(this->socketServidor,(struct sockaddr*)&servidor,sizeof(struct sockaddr)))<0){
		cout<<"error en el enlace"<<endl;
	};
}
void Servidor::esperarConexiones(){
	listen(this->socketServidor,3);
	puts("Esperando conexiones");
	int tamanioCliente=sizeof(cliente);
	pthread_t thread_id;
	Cliente * infoCliente=(Cliente*)malloc(sizeof(Cliente));
	while(true){
		if(this->cantidadDeClientes<CANT_MAX_CLIENTES){
			this->socketCliente=accept(this->socketServidor,(struct sockaddr*)&cliente,(socklen_t*)&tamanioCliente);
			if(this->socketCliente<0){
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
			int algo=accept(this->socketServidor,(struct sockaddr*)&cliente,(socklen_t*)&tamanioCliente);
			this->sisEnvio.enviarString("Juego Completo",algo);
		}
	}
}
void Servidor::enviarIdCliente(int idCliente,int socketCliente){
	this->sisEnvio.enviarString("Conectado",socketCliente);
	this->sisEnvio.enviarEntero(idCliente,socketCliente);
}

void *Servidor::conexionCliente(void*cliente){
	Cliente* argumentos = (Cliente*) cliente;
	((Servidor*)argumentos->servidor)->enviarIdCliente(argumentos->id,argumentos->socket);
}

