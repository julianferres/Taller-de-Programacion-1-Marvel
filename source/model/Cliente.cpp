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

struct infoCliente {
		Cliente *cliente;
		int ssocket;
 };
 typedef struct infoCliente iCliente;

Cliente::Cliente( char * direccionIP,int puerto){
	iCliente* args = (iCliente*) malloc(sizeof(infoCliente));
	args->cliente=this;
	juegoCliente = new JuegoCliente();
	this->iniciarConexion(direccionIP,puerto);
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
	args->ssocket=numeroSocket;
	pthread_t thread_id;
	pthread_create( &thread_id , NULL , &Cliente::enviarEventosWrapper ,(void*)args);

	while(true){
		recibirParaDibujar();
	}

	close(numeroSocket);
}


void Cliente::iniciarConexion(char* direccionIP,int puerto){
	int  conexion;
	struct hostent *nodoServidor;
	struct sockaddr_in servidor;

	nodoServidor=gethostbyname(direccionIP);
	if(nodoServidor==NULL)
		controladorLogger->registrarEvento("ERROR", "Cliente::Error en la conexion");

	numeroSocket=socket(AF_INET, SOCK_STREAM, 0);
	servidor.sin_family=AF_INET;
	servidor.sin_port=htons(puerto);
	servidor.sin_addr=*((struct in_addr *)nodoServidor->h_addr);
	bzero(&(servidor.sin_zero),8);
	conexion=connect(numeroSocket,(struct sockaddr *)&servidor,sizeof(struct sockaddr));
	if(conexion==-1)
		controladorLogger->registrarEvento("ERROR", "Cliente::Error al conectar con el servidor");
	this->idCliente=this->sistemaEnvio.recibirEntero(numeroSocket);
	cout<<"Conectado..."<<endl;
	cout<<"tengo id: "<<this->idCliente<<endl;
}





void Cliente::recibirParaDibujar(){

	char fondo1[MAXDATOS];
	char fondo2[MAXDATOS];
	char fondo3[MAXDATOS];
	char personaje1[MAXDATOS];
	char personaje2[MAXDATOS];
	int posicion1[8];
	int posicion2[8];
	int posicion3[8];
	int posicion4[8];
	int posicion5[8];
	SDL_RendererFlip flipFondo1,flipFondo2,flipFondo3,flipPersonaje1,flipPersonaje2;

	while(true){

		recv(numeroSocket,posicion1,sizeof(posicion1),MSG_WAITALL);
		recv(numeroSocket,posicion2,sizeof(posicion2),MSG_WAITALL);
		recv(numeroSocket,posicion3,sizeof(posicion3),MSG_WAITALL);
		recv(numeroSocket,posicion4,sizeof(posicion4),MSG_WAITALL);
		recv(numeroSocket,posicion5,sizeof(posicion5),MSG_WAITALL);

		recv(numeroSocket,fondo1,MAXDATOS,MSG_WAITALL);
		recv(numeroSocket,fondo2,MAXDATOS,MSG_WAITALL);
		recv(numeroSocket,fondo3,MAXDATOS,MSG_WAITALL);
		recv(numeroSocket,personaje1,MAXDATOS,MSG_WAITALL);
		recv(numeroSocket,personaje2,MAXDATOS,MSG_WAITALL);

		recv(numeroSocket,&flipFondo1,sizeof(flipFondo1),MSG_WAITALL);
		recv(numeroSocket,&flipFondo2,sizeof(flipFondo2),MSG_WAITALL);
		recv(numeroSocket,&flipFondo3,sizeof(flipFondo3),MSG_WAITALL);
		recv(numeroSocket,&flipPersonaje1,sizeof(flipPersonaje1),MSG_WAITALL);
		recv(numeroSocket,&flipPersonaje2,sizeof(flipPersonaje2),MSG_WAITALL);

		juegoCliente->graficos()->limpiar();
		juegoCliente->dibujar(string(fondo1),posicion1,flipFondo1);
		juegoCliente->dibujar(string(fondo2),posicion2,flipFondo2);
		juegoCliente->dibujar(string(fondo3),posicion3,flipFondo3);
		juegoCliente->dibujar(string(personaje1),posicion4,flipPersonaje1);
		juegoCliente->dibujar(string(personaje2),posicion5,flipPersonaje2);
		juegoCliente->graficos()->render();

	}
}
void *Cliente::enviarEventosWrapper(void* arg){
	iCliente* argumentos = (iCliente*) arg;
	((Cliente *)argumentos->cliente)->enviarEventos(argumentos->ssocket);
	return NULL;
}
void Cliente::enviarEventos(int socket){
	while(true){
		SDL_Event evento;
		while(SDL_PollEvent(&evento)){
			if(evento.type==SDL_KEYDOWN || evento.type==SDL_KEYUP || evento.type==SDL_QUIT){
				this->sistemaEnvio.enviarEntero(this->idCliente,socket);
				send(socket,&evento,sizeof(evento),0);
			}
		}
	}
}

