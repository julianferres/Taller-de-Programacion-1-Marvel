#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <Cliente.hpp>
#include <string>
#include <tuple>

using namespace std;

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;

Cliente::Cliente( char * direccionIP){
	juegoCliente = new JuegoCliente();
	this->iniciarConexion(direccionIP);
	juegoCliente->iniciarGraficos();
	const string &filePath1 = controladorJson->pathImagen(string("Venom"));
	tuple <string, const string> tuplaPersonaje1=make_tuple(string("Venom"),filePath1);
	const string &filePath2 = controladorJson->pathImagen(string("Spiderman"));
	tuple <string, const string> tuplaPersonaje2=make_tuple(string("Spiderman"),filePath2);
	personajesYfondos.push_back(tuplaPersonaje1);
	personajesYfondos.push_back(tuplaPersonaje2);

	for(int i=1;i<4;i++){
		const string &filePath = controladorJson->pathFondo(i);
		tuple <string, const string> tuplaFondo=make_tuple(to_string(i),filePath);
		personajesYfondos.push_back(tuplaFondo);
	}
	juegoCliente->cargarTexturas(personajesYfondos);
	pthread_t thread_id;
	int *arg = (int*)malloc(sizeof(*arg));
	*arg = numeroSocket;
	pthread_create( &thread_id , NULL , &Cliente::enviarEventos , arg);

	while(true){
		recibirParaDibujar();
	}

	close(numeroSocket);
}


void Cliente::iniciarConexion(char* direccionIP){
	int  conexion;
	struct hostent *nodoServidor;
	struct sockaddr_in servidor;

	nodoServidor=gethostbyname(direccionIP);
	if(nodoServidor==NULL)
		controladorLogger->registrarEvento("ERROR", "Cliente::Error en la conexion");

	numeroSocket=socket(AF_INET, SOCK_STREAM, 0);
	servidor.sin_family=AF_INET;
	servidor.sin_port=htons(PUERTO);
	servidor.sin_addr=*((struct in_addr *)nodoServidor->h_addr);
	bzero(&(servidor.sin_zero),8);
	conexion=connect(numeroSocket,(struct sockaddr *)&servidor,sizeof(struct sockaddr));
	if(conexion==-1)
		controladorLogger->registrarEvento("ERROR", "Cliente::Error al conectar con el servidor");
	puts("Conectado...");
}





void Cliente::recibirParaDibujar(){
	//int i=0;
	char fondo1[MAXDATOS];
	char fondo2[MAXDATOS];
	char fondo3[MAXDATOS];
	char personaje1[MAXDATOS];
	char personaje2[MAXDATOS];
	SDL_RendererFlip flipFondo1,flipFondo2,flipFondo3,flipPersonaje1,flipPersonaje2;

	while(true){

		int posicion1[8];
		int posicion2[8];
		int posicion3[8];
		int posicion4[8];
		int posicion5[8];

		recv(numeroSocket,posicion1,sizeof(posicion1),0);
		recv(numeroSocket,posicion2,sizeof(posicion2),0);
		recv(numeroSocket,posicion3,sizeof(posicion3),0);
		recv(numeroSocket,posicion4,sizeof(posicion4),0);
		recv(numeroSocket,posicion5,sizeof(posicion5),0);

		recv(numeroSocket,fondo1,MAXDATOS,0);
		recv(numeroSocket,fondo2,MAXDATOS,0);
		recv(numeroSocket,fondo3,MAXDATOS,0);
		recv(numeroSocket,personaje1,MAXDATOS,0);
		recv(numeroSocket,personaje2,MAXDATOS,0);

		recv(numeroSocket,&flipFondo1,sizeof(flipFondo1),0);
		recv(numeroSocket,&flipFondo2,sizeof(flipFondo2),0);
		recv(numeroSocket,&flipFondo3,sizeof(flipFondo3),0);
		recv(numeroSocket,&flipPersonaje1,sizeof(flipPersonaje1),0);
		recv(numeroSocket,&flipPersonaje2,sizeof(flipPersonaje2),0);
		juegoCliente->graficos()->limpiar();
		juegoCliente->dibujar(string(fondo1),posicion1,flipFondo1);
		juegoCliente->dibujar(string(fondo2),posicion2,flipFondo2);
		juegoCliente->dibujar(string(fondo3),posicion3,flipFondo3);
		juegoCliente->dibujar(string(personaje1),posicion4,flipPersonaje1);
		juegoCliente->dibujar(string(personaje2),posicion5,flipPersonaje2);

		juegoCliente->graficos()->render();

		//puts(to_string(i).c_str());
		//i++;
	}


}

void *Cliente::enviarEventos(void* arg){
	int socketConexion=*(int*)arg;
	while(true){
		SDL_Event evento;
		while(SDL_PollEvent(&evento)){
			if(evento.type==SDL_KEYDOWN || evento.type==SDL_KEYUP || evento.type==SDL_QUIT){
				send(socketConexion,&evento,sizeof(evento),0);
			}
		}
	}

}








