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
		if( pthread_create( &thread_id , NULL , Server::conexionConClienteWrapper , (void*) args)  < 0)
			controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo crear el hilo .");

		cantidad_actual_clientes++;
		//pthread_join( thread_id , NULL);
		cout<<"Bienvenido jugador "+to_string(cantidad_actual_clientes)<<endl;

	}
	free(args);
}



void *Server::conexionConClienteWrapper(void *args){
	parametros* argumentos = (parametros*) args;
	 return ((Server *)argumentos->este)->conexionConCliente((void*)&argumentos->client_sock);
}
 
void *Server::conexionConCliente(void *socket_desc){

	int sock = *(int*)socket_desc;
	int *idCliente = (int*) malloc(sizeof(int));
	char nombrePersonaje[MAXDATOS];
	*idCliente = cantidad_actual_clientes;//El id es segun el orden en que hayan llegado los jugadores

	while(cantidad_actual_clientes<CANTIDAD_MAXIMA_JUGADORES){
	}

	send(sock,&*idCliente,sizeof(*idCliente),0);//envio al cliente su id, y le aviso que ya estan todos conectados
	recv(sock,nombrePersonaje,MAXDATOS,0);   //recibo el personaje elegido

	this->crearJugador(nombrePersonaje, *idCliente);

	while(vectorPersonajes.size()<CANTIDAD_MAXIMA_JUGADORES){
	}

	this->enviarNombresJugadores(sock);
	this->enviarFondos(sock);

	while(true){}

	return 0;
} 

void Server::enviarNombresJugadores(int socketCliente){
	mutex personajes_mutex;
	personajes_mutex.lock();
	for(int i=0; i <CANTIDAD_MAXIMA_JUGADORES;i++){
		char* personajeElegido = vectorPersonajes[i];
		send(socketCliente,personajeElegido,MAXDATOS,0);//le envio el personaje al cliente
		recv(socketCliente,buffer,MAXDATOS,0); //significa que le llego y puedo seguir
		cout<<socketCliente<<endl;
	}
	personajes_mutex.unlock();

}

void Server::enviarFondos(int socketCliente){
	cout<<socketCliente<<endl;
	vector<int>zindexes = controladorJson->getZindexes();
	int cantidadZindex = zindexes.size();
	int zindexAenviar[cantidadZindex] ;
	for(int i=0;i<zindexes.size();i++){
		zindexAenviar[i] = zindexes[i];
	}
	send(socketCliente,zindexAenviar,sizeof(zindexAenviar),0);
}

void Server::crearJugador(char* nombrePersonaje, int idCliente){
	mutex personajes_mutex;
	personajes_mutex.lock();
	juego->crearJugador(string(nombrePersonaje),idCliente);
	vectorPersonajes.push_back(nombrePersonaje);
	personajes_mutex.unlock();
}

void Server::enviarParaDibujar(int socketCliente){
	vector<tuple<string,SDL_Rect , SDL_Rect >> dibujables=juego->dibujar();
	for(int i=0;i<dibujables.size();i++){
		string nombre = get<0>(dibujables[i]);
		send(socketCliente,nombre.c_str(),MAXDATOS,0);
		recv(socketCliente,buffer,MAXDATOS,0);
		SDL_Rect origen = get<1>(dibujables[i]);
		SDL_Rect destino = get<2>(dibujables[i]);
		int posiciones[8] ;
		posiciones[0]=origen.x;
		posiciones[1]=origen.y;
		posiciones[2]=origen.w;
		posiciones[3]=origen.h;
		if(!destino.w){//revisar
			posiciones[4]=-1;
			posiciones[5]=-1;
			posiciones[6]=-1;
			posiciones[7]=-1;
		}
		else{
			posiciones[4]=destino.x;
			posiciones[5]=destino.y;
			posiciones[6]=destino.w;
			posiciones[7]=destino.h;
		}
		send(socketCliente,posiciones,sizeof(posiciones),0);
		recv(socketCliente,buffer,MAXDATOS,0);
	}
}
