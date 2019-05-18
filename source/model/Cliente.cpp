#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
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
	this->iniciarConexion(direccionIP,puerto);
	if(idCliente == -1){//significa que el server esta lleno, me cierro
		controladorLogger->registrarEvento("ERROR", "Cliente::El server esta lleno.");
		close(numeroSocket);
		return;
	}

	iCliente* args = (iCliente*) malloc(sizeof(infoCliente));
	args->cliente=this;
	juegoCliente = new JuegoCliente();
	juegoCliente->iniciarGraficos();

	vector<string> personajes = controladorJson->getNombresPersonajes();
	for(size_t i=0;i<personajes.size();i++){
		const string &filePath = controladorJson->pathImagen(personajes[i]);
		personajesYfondos.push_back(make_tuple(personajes[i],filePath));
	}
	vector<int> fondos = controladorJson->getZindexes();
	for(size_t i=0;i<fondos.size();i++){
		const string &filePath = controladorJson->pathFondo(fondos[i]);
		personajesYfondos.push_back(make_tuple(to_string(fondos[i]),filePath));
	}

	juegoCliente->cargarTexturas(personajesYfondos);
	args->ssocket=numeroSocket;

	pthread_t thread_id;
	pthread_create( &thread_id , NULL , &Cliente::enviarEventosWrapper ,(void*)args);
	recibirParaDibujar();

	pthread_join(thread_id, NULL);
	delete juegoCliente;
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
	else
		controladorLogger->registrarEvento("INFO", "Cliente::Conectado al servidor correctamente.");

	this->idCliente=this->sistemaEnvio.recibirEntero(numeroSocket);
	cout<<"Conectado..."<<endl;

}





void Cliente::recibirParaDibujar(){

	char textura[MAXDATOS];
	int posiciones[8];
	SDL_RendererFlip flip;

	while(true){
		juegoCliente->graficos()->limpiar();

		for(int i=0;i<5;i++){
			if(recv(numeroSocket,textura,MAXDATOS,MSG_WAITALL)==0){
				controladorLogger->registrarEvento("ERROR", "Cliente::Se desconecto el server. Procedo a cerrarme ");
				running = false;
				return;
			}
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
	while(running){
		while(SDL_PollEvent(&evento)){
			if(evento.type==SDL_KEYDOWN || evento.type==SDL_KEYUP || evento.type==SDL_QUIT){
				this->sistemaEnvio.enviarEntero(this->idCliente,socket);
				send(socket,&evento,sizeof(evento),0);
			}
		}
	}
}

