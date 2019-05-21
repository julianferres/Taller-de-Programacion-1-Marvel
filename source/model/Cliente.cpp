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
	juegoCliente->iniciarGraficos(idCliente);
	this->cargarContenidos();
	args->ssocket=numeroSocket;
	juegoCliente->cargarTexturas(personajesYfondos);
	this->recibirTitulos();

	pthread_t thread_id;
	pthread_create( &thread_id , NULL , &Cliente::enviarEventosWrapper ,(void*)args);
	recibirParaDibujar();

	pthread_join(thread_id, NULL);
	delete juegoCliente;
	close(numeroSocket);
}


void Cliente::cargarContenidos(){
	vector<string> personajes = controladorJson->getNombresPersonajes();
	for(size_t i=0;i<personajes.size();i++){
		const string &filePath = controladorJson->pathImagen(personajes[i]);
		personajesYfondos.push_back(make_tuple(personajes[i],filePath));
		const string &buttonPath = controladorJson->pathBoton((personajes[i]));
		personajesYfondos.push_back(make_tuple(personajes[i]+"Boton",buttonPath));
	}
	vector<int> fondos = controladorJson->getZindexes();
	for(size_t i=0;i<fondos.size();i++){
		const string &filePath = controladorJson->pathFondo(fondos[i]);
		personajesYfondos.push_back(make_tuple(to_string(fondos[i]),filePath));
	}
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
	int size;
	while(running){
		juegoCliente->graficos()->limpiar();
		recv(numeroSocket,&size,sizeof(size),MSG_WAITALL);
		if(size==-1){
			enMenu=false;
			continue;
		}
		for(int i=0;i<size;i++){
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
	int beat=1;
	send(socket,&beat,sizeof(beat),0);
	while(running){
		send(socket,&beat,sizeof(beat),0);
		while(SDL_PollEvent(&evento)){
			if(enMenu){
				if(evento.type==SDL_MOUSEBUTTONDOWN||evento.type==SDL_MOUSEBUTTONUP
					||evento.type== SDL_MOUSEMOTION)
					send(socket,&evento,sizeof(evento),0);
			}
			else{
				if(evento.type==SDL_KEYDOWN || evento.type==SDL_KEYUP || evento.type==SDL_QUIT)
					send(socket,&evento,sizeof(evento),0);
				if(evento.type==SDL_QUIT){
					running=false;
					return;
				}
			}
		}
	}
}

void Cliente::recibirTitulos(){
	vector<tuple<string,string,int,string,int ,int ,int >>titulos;
	char nombre[MAXDATOS];
	char path[MAXDATOS];
	int size;
	char descripcion[MAXDATOS];
	int r,g,b;
	int cantidadTitulos;
	recv(numeroSocket,&cantidadTitulos,sizeof(cantidadTitulos),MSG_WAITALL);
	for(size_t i=0;i<cantidadTitulos;i++){
		recv(numeroSocket,nombre,MAXDATOS,MSG_WAITALL);
		recv(numeroSocket,path,MAXDATOS,MSG_WAITALL);
		recv(numeroSocket,&size,sizeof(size),MSG_WAITALL);
		recv(numeroSocket,descripcion,MAXDATOS,MSG_WAITALL);
		recv(numeroSocket,&r,sizeof(r),MSG_WAITALL);
		recv(numeroSocket,&g,sizeof(g),MSG_WAITALL);
		recv(numeroSocket,&b,sizeof(b),MSG_WAITALL);
		titulos.push_back(make_tuple(string(nombre),string(path),size,string(descripcion),r,g,b));
	}
	this->juegoCliente->cargarTitulosMenu(titulos);
}
