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
 
using namespace std;

Server::Server()
{
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
    cantidad_actual_clientes=0;

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

    while(cantidad_actual_clientes<4 ){
    	puts("Connection accepted");
    	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        if( pthread_create( &thread_id , NULL , (THREADFUNCPTR) &Server::connection_handler , (void*) &client_sock) < 0)
        	perror("could not create thread");

        cantidad_actual_clientes++;
        //pthread_join( thread_id , NULL);
        puts("Handler assigned");
    }
     
    if (client_sock < 0)
        perror("accept failed");
     

}
 
/*
 * This will handle connection for each client
 * */
void *Server::connection_handler(void *socket_desc)
{
    //puts("Soy la funcion de conexion con el cliente");
    int sock = *(int*)socket_desc;
    unsigned int *idCliente;
    *idCliente = Server::cantidad_actual_clientes;

   char mensaje[256];

   while(cantidad_actual_clientes<3){
    	puts("esperar a que estemos todos");
    	//send(sock,NULL,sizeof(NULL),0);
    }
   send(sock,idCliente,sizeof(int*),0);//envio al cliente su id, y le aviso que ya estan todos conectados
   recv(sock,mensaje,256,0);//recibo el personaje elegido
   const string &filePath = controladorJson->pathImagen(mensaje);
   tuple <string, const string> personaje=make_tuple(mensaje,filePath);
   personajes.push_back(personaje);
   while(personajes.size()<4){
	   puts("hay jugadores que no seleccionaron todavia");
   }
   for(int i=0;i<4;i++){
	   string nombre = get<0>(personajes[i]);
	   juego->crearJugador(nombre,*idCliente);
   }
   juego->crearEquipos();

   send(sock,&personajes,sizeof(personajes),0);//le enviamos para que creen las texturas

   juego->gameLoop();




    while(  mensaje!="salir" ){
    	recv(sock,mensaje,256,0);
    	cout<<mensaje<<endl;
    	cin>>mensaje;
    	send(sock,mensaje,256,0);
    }
     

         
    return 0;
} 
