#include<Server.hpp>
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <mutex>

using namespace std;

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

struct arg_struct {
		Server *este;
		int client_sock;
	 }args;
	 typedef struct arg_struct parametros;


 Server::Server(){
	juego = new Juego();
	this->crearSocket();
	this->esperarConexiones();

	 while(true){
	 }

	 close(socketServidor);

 }

void Server::crearSocket(){
   socketServidor = socket(AF_INET , SOCK_STREAM , 0);
	if (socketServidor == -1)
		controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo crear el socket .");
	else
		controladorLogger->registrarEvento("INFO", "Servidor::Socket creado.");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( PUERTO );

	if( bind(socketServidor,(struct sockaddr *)&server , sizeof(server)) < 0)
		perror("bind failed. Error");
}

void Server::esperarConexiones(){
	parametros* args = (parametros*) malloc(sizeof(arg_struct));
	args->este=this;

	listen(socketServidor , 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	int c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	while( vectorPersonajes.size() < CANTIDAD_MAXIMA_JUGADORES){
		socketCliente = accept(socketServidor, (struct sockaddr *)&client, (socklen_t*)&c);
		 if (socketCliente < 0)
			 controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo aceptar la conexion .");
		args->client_sock=socketCliente;
		puts("Connection accepted");
		if( pthread_create( &thread_id , NULL , Server::connection_handler_wrapper , (void*) args)  < 0)
			controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo crear el hilo .");

		cantidad_actual_clientes++;
		//pthread_join( thread_id , NULL);
		cout<<"Bienvenido jugador "+to_string(cantidad_actual_clientes)<<endl;

	}
	free(args);
}



void *Server::connection_handler_wrapper(void *args){
	parametros* argumentos = (parametros*) args;
	 return ((Server *)argumentos->este)->conexionInicial((void*)&argumentos->client_sock);
}
 
void *Server::conexionInicial(void *socket_desc)
{
	mutex personajes_mutex;
    int sock = *(int*)socket_desc;
    int *idCliente = (int*) malloc(sizeof(int));
    char nombrePersonaje[MAXDATOS];
    char buffer[MAXDATOS];
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
		recv(sock,buffer,MAXDATOS,0); //significa que le llego y puedo seguir
   }

   std::vector<int>zindexes = controladorJson->getZindexes();
   for(int i=0;i<zindexes.size();i++){
	   int zindex = zindexes[i];
	   send(sock,&zindex,sizeof(zindex),0);
	   recv(sock,buffer,MAXDATOS,0); //significa que le llego y puedo seguir
   }

   while(true){}

   //juego->gameLoop();

         
    return 0;
} 
