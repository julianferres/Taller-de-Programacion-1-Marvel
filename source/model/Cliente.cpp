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

	char textura[MAXDATOS];
	int posiciones[8];
	SDL_RendererFlip flip;

	while(true){
		juegoCliente->graficos()->limpiar();

		for(int i=0;i<5;i++){
			recv(numeroSocket,textura,MAXDATOS,MSG_WAITALL);
			recv(numeroSocket,posiciones,sizeof(posiciones),MSG_WAITALL);
			recv(numeroSocket,&flip,sizeof(flip),MSG_WAITALL);
			juegoCliente->dibujar(string(textura),posiciones,flip);
		}

		juegoCliente->graficos()->render();
	}
}

void *Cliente::enviarEventosWrapper(void* arg){
	iCliente* argumentos = (iCliente*) arg;
	((Cliente *)argumentos->cliente)->enviarEventos(argumentos->ssocket);
	return NULL;
}

void Cliente::enviarEventos(int socket){
	SDL_Event evento;
	while(true){
		while(SDL_PollEvent(&evento)){
			if(evento.type==SDL_KEYDOWN || evento.type==SDL_KEYUP || evento.type==SDL_QUIT){
				this->sistemaEnvio.enviarEntero(this->idCliente,socket);
				send(socket,&evento,sizeof(evento),0);
			}
		}
	}
}

