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
	this->crearThreadServer();
	this->crearSocket();
	this->esperarConexiones();

	 close(socketServidor);
}

 void Server::crearThreadServer(){
	pthread_t thread_id;
	if( pthread_create( &thread_id , NULL , Server::actualizarModeloWrapper , this)  < 0)
		controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo crear el hilo del servidor");

}

 void* Server::actualizarModeloWrapper(void *args){
 	 Server* serv = (Server * )args;
 	 return serv->actualizarModelo();
}



  void *Server::actualizarModelo(){
	  juego = new Juego();
	  juego->crearJugador("Venom", 1);
	  juego->crearJugador("Venom", 2);
	  juego->crearJugador("Venom", 3);
	  juego->crearJugador("Venom", 4);
	  juego->crearEquipos();

	  while(true){}


 	return NULL;
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
	puts("Waiting for incoming connections...");

	int c = sizeof(struct sockaddr_in);
	pthread_t thread_enviar;
	pthread_t thread_recibir;
	while( true){
		socketCliente = accept(socketServidor, (struct sockaddr *)&client, (socklen_t*)&c);
		 if (socketCliente < 0)
			 controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo aceptar la conexion .");
		args->client_sock=socketCliente;
		puts("Connection accepted");

		if( pthread_create( &thread_enviar , NULL , Server::enviarParaDibujarWrapper , (void*) args)  < 0)
			controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo crear el hilo .");
		if( pthread_create( &thread_recibir , NULL , Server::recibirTeclasWrapper , (void*) args)  < 0)
			controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo crear el hilo .");
		clientesConectados.push_back(socketCliente);
		cantidad_actual_clientes++;
		cout<<"Bienvenido jugador "+to_string(cantidad_actual_clientes)<<endl;

	}
	free(args);
}

void *Server::recibirTeclasWrapper(void *args){
	parametros* argumentos = (parametros*) args;
	 return ((Server *)argumentos->este)->recibirTeclas((void*)&argumentos->client_sock);
}


void *Server::enviarParaDibujarWrapper(void *args){
	parametros* argumentos = (parametros*) args;
	 return ((Server *)argumentos->este)->enviarParaDibujar((void*)&argumentos->client_sock);
}
 
void *Server::enviarParaDibujar(void *socket_desc){
	int socket = *((int *)socket_desc);
	int i=0;
	char fondo1[MAXDATOS];
	char fondo2[MAXDATOS];
	char fondo3[MAXDATOS];
	char personaje1[MAXDATOS];
	char personaje2[MAXDATOS];
	vector<tuple<string,SDL_Rect , SDL_Rect >> dibujablesThread;
	Uint32 tiempoInicial;

	while(true){
		tiempoInicial= SDL_GetTicks();
		dibujablesThread= juego->dibujar();
		SDL_Rect rect1 =get<1>(dibujablesThread[0]);
		SDL_Rect rect2 =get<2>(dibujablesThread[0]);
		SDL_Rect rect3 =get<1>(dibujablesThread[1]);
		SDL_Rect rect4 =get<2>(dibujablesThread[1]);
		SDL_Rect rect5 =get<1>(dibujablesThread[2]);
		SDL_Rect rect6 =get<2>(dibujablesThread[2]);
		SDL_Rect rect7 =get<1>(dibujablesThread[3]);
		SDL_Rect rect8 =get<2>(dibujablesThread[3]);
		SDL_Rect rect9 =get<1>(dibujablesThread[4]);
		SDL_Rect rect10 =get<2>(dibujablesThread[4]);

		int posicion1[8]={rect1.x,rect1.y,rect1.w,rect1.h,rect2.x,rect2.y,rect2.w,rect2.h};
		int posicion2[8]={rect3.x,rect3.y,rect3.w,rect3.h,rect4.x,rect4.y,rect4.w,rect4.h};
		int posicion3[8]={rect5.x,rect5.y,rect5.w,rect5.h,rect6.x,rect6.y,rect6.w,rect6.h};
		int posicion4[8]={rect7.x,rect7.y,rect7.w,rect7.h,rect8.x,rect8.y,rect8.w,rect8.h};
		int posicion5[8]={rect9.x,rect9.y,rect9.w,rect9.h,rect10.x,rect10.y,rect10.w,rect10.h};

		send(socket,posicion1,sizeof(posicion1),0);
		send(socket,posicion2,sizeof(posicion2),0);
		send(socket,posicion3,sizeof(posicion3),0);
		send(socket,posicion4,sizeof(posicion4),0);
		send(socket,posicion5,sizeof(posicion5),0);


		strcpy(fondo1,  get<0>(dibujablesThread[0]).c_str());
		strcpy(fondo2,  get<0>(dibujablesThread[1]).c_str());
		strcpy(fondo3,  get<0>(dibujablesThread[2]).c_str());
		strcpy(personaje1,  get<0>(dibujablesThread[3]).c_str());
		strcpy(personaje2,  get<0>(dibujablesThread[4]).c_str());

		send(socket,fondo1,MAXDATOS,0);
		send(socket,fondo2,MAXDATOS,0);
		send(socket,fondo3,MAXDATOS,0);
		send(socket,personaje1,MAXDATOS,0);
		send(socket,personaje2,MAXDATOS,0);

		if(SDL_GetTicks() - tiempoInicial < 1000/60)
			SDL_Delay( 1000/60 - SDL_GetTicks() +tiempoInicial );

		puts(to_string(i).c_str());
		i++;

	}

	return 0;
} 

void* Server::recibirTeclas(void* socket_desc){
	SDL_Event evento;
	int socket = *((int *)socket_desc);
	while(true){
		recv(socket,&evento,sizeof(evento),0);
		mutex juegoMutex;
		juegoMutex.lock();
		juego->teclear(evento);
		juegoMutex.unlock();
	}

}




