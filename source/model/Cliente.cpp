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
		cout<<"El servidor esta lleno. Este cliente se va a desconectar."<<endl;
		controladorLogger->registrarEvento("ERROR", "Cliente::El server esta lleno, me desconecto.");
		this->partidallena();
		close(numeroSocket);
		return;
	}
	if(idCliente==0){
		cout<<"Servidor no encontrado."<<endl;
		close(numeroSocket);
		return;
	}
	cout<<"Conectado al servidor con exito."<<endl;
	struct timeval tv = {2, 0};
	setsockopt(numeroSocket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
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
	cout<<"Conexion finalizada."<<endl;
	controladorLogger->registrarEvento("INFO", "Cliente::Conexion finalizada.");
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
	personajesYfondos.push_back(make_tuple(string("Fondo"), string("contents/images/fondo.png")));
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
	if(conexion==-1){
		controladorLogger->registrarEvento("ERROR", "Cliente::Error al conectar con el servidor");
		this->idCliente=0;
		return;
	}
	controladorLogger->registrarEvento("INFO", "Cliente::Conectado al servidor correctamente.");
	this->idCliente=this->sistemaEnvio.recibirEntero(numeroSocket);

}

void Cliente::partidallena(){
	bool close=false;
	SDL_Event eventoLLeno;
	SDL_Init( SDL_INIT_VIDEO );
	SDL_Window* ventana;
	SDL_Renderer* rendererizar;
	SDL_CreateWindowAndRenderer(800,600, false, &ventana, &rendererizar);
	SDL_SetWindowTitle(ventana, "Marvel vs Capcom");
	SDL_Surface* fondo = IMG_Load("contents/images/partidaLLena.png");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(rendererizar, fondo);
	while (!close){
		SDL_WaitEvent(&eventoLLeno);
		switch (eventoLLeno.type)
		{
		case SDL_QUIT:
			close = true;
			break;
		}
		SDL_RenderCopy(rendererizar, texture, NULL, NULL);
		SDL_RenderPresent(rendererizar);
		}
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(fondo);
	SDL_DestroyRenderer(rendererizar);
	SDL_DestroyWindow(ventana);
}

void Cliente::recibirParaDibujar(){
	SDL_Event evento;
	evento.type = SDL_MOUSEWHEEL;
	char textura[MAXDATOS];
	int posiciones[8];
	SDL_RendererFlip flip;
	int size;
	int recibido;
	while(running){
		recibido = recv(numeroSocket,&size,sizeof(size),MSG_WAITALL);
		if(recibido<0){
			if(conectado)
				cout<<"Conexion perdida con el servidor."<<endl;
			cout<<"Intentando reconectar con el servidor..."<<endl;
			conectado = false;
			continue;
		}
		if(recibido == 0){
			cout<<"El servidor se ha cerrado. Este cliente se va a desconectar."<<endl;
			running = false;
			return;
		}
		if(!conectado)
			cout<<"Reconectado con el servidor."<<endl;
		conectado = true;
		if(size==-1){
			enMenu=false;
			continue;
		}
		juegoCliente->graficos()->limpiar();
		for(int i=0;i<size;i++){
			recv(numeroSocket,textura,MAXDATOS,MSG_WAITALL);
			recv(numeroSocket,posiciones,sizeof(posiciones),MSG_WAITALL);
			recv(numeroSocket,&flip,sizeof(flip),MSG_WAITALL);
			juegoCliente->dibujar(string(textura),posiciones,flip);
		}
		juegoCliente->graficos()->render();
		send(numeroSocket,&evento,sizeof(evento),0);//heartbeat
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
			if(!conectado) continue;
			if(evento.type==SDL_QUIT){
				running=false;
				return;
			}
			if(enMenu){
				if(evento.type==SDL_MOUSEBUTTONDOWN||evento.type==SDL_MOUSEBUTTONUP
					||evento.type== SDL_MOUSEMOTION)
					send(socket,&evento,sizeof(evento),0);
			}
			else{
				if(evento.type==SDL_KEYDOWN || evento.type==SDL_KEYUP )
					send(socket,&evento,sizeof(evento),0);
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
