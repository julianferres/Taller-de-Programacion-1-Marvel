#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<Server.hpp>
#include <iostream>
#include<Juego.hpp>
#include <vector>
#include <tuple>
#include <string>
#include <mutex>
#define CANTIDAD_MAXIMA_JUGADORES 4
#define MAXDATOS 1000
using namespace std;

struct arg_struct {
	    Server *este;
	    int client_sock;
	 }args;
	typedef struct arg_struct parametros;


Server::Server()
{
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
    cantidad_actual_clientes=0;

    parametros* args = (parametros*) malloc(sizeof(arg_struct));
   args->este=this;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
        printf("Could not create socket");

    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 5001 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        perror("bind failed. Error");

    puts("bind done");
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

	pthread_t thread_id;
	juego = new Juego();

    while( vectorPersonajes.size() < CANTIDAD_MAXIMA_JUGADORES){
    	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    	 if (client_sock < 0)
    	        perror("accept failed");
    	args->client_sock=client_sock;
    	puts("Connection accepted");
    	if( pthread_create( &thread_id , NULL , Server::connection_handler_wrapper , (void*) args)  < 0)
        	perror("could not create thread");

        cantidad_actual_clientes++;
        //pthread_join( thread_id , NULL);
        cout<<"Bienvenido jugador "+to_string(cantidad_actual_clientes)<<endl;

    }

    juego->crearEquipos();
    while(true){
    }

    free(args);
    close(socket_desc);

}

void *Server::connection_handler_wrapper(void *args){
	parametros* argumentos = (parametros*) args;
	 return ((Server *)argumentos->este)->connection_handler((void*)&argumentos->client_sock);
}
 
/*
 * This will handle connection for each client
 * */
void *Server::connection_handler(void *socket_desc)
{
	mutex personajes_mutex;
    int sock = *(int*)socket_desc;
    int *idCliente = (int*) malloc(sizeof(int));
    char nombrePersonaje[MAXDATOS];

    //El id es segun el orden en que hayan llegado los jugadores
    *idCliente = cantidad_actual_clientes;

   while(cantidad_actual_clientes<CANTIDAD_MAXIMA_JUGADORES){
	   //esperando que lleguen todos los jugadores
    }

   //Convierto el id en bytes para que sean enviados
	int idConvertidoParaEnviar = htonl(*idCliente);
   send(sock,(const char *)&idConvertidoParaEnviar,sizeof(int),0);//envio al cliente su id, y le aviso que ya estan todos conectados

   //recibo el personaje elegido
   recv(sock,nombrePersonaje,MAXDATOS,0);
   personajes_mutex.lock();
   juego->crearJugador(string(nombrePersonaje),*idCliente);
   vectorPersonajes.push_back(nombrePersonaje);//creo al jugador
   personajes_mutex.unlock();

   while(vectorPersonajes.size()<CANTIDAD_MAXIMA_JUGADORES){
	   //puts("hay jugadores que no seleccionaron todavia");
   }

   for(int i=0; i <CANTIDAD_MAXIMA_JUGADORES;i++){
		char* personajeElegido = vectorPersonajes[i];
		send(sock,personajeElegido,MAXDATOS,0);//le envio el personaje al cliente
   }

   while(true){}
   //juego->gameLoop();




    while(nombrePersonaje!="salir" ){
    	recv(sock,nombrePersonaje,256,0);
    	cout<<nombrePersonaje<<endl;
    	cin>>nombrePersonaje;
    	send(sock,nombrePersonaje,256,0);
    }
     

         
    return 0;
} 
