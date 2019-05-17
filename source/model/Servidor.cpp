#include <Servidor.hpp>
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <mutex>

using namespace std;

extern ControladorJson *controladorJson;
extern ControladorLogger *controladorLogger;
mutex server_mutex;

struct infoServidor {
		Servidor *servidor;
		int csocket;
 };
 typedef struct infoServidor iServidor;


 Servidor::Servidor(int puerto){
	this->crearThreadServer();
	this->crearSocket(puerto);
	this->esperarConexiones();

	 close(socketServidor);
}

 void Servidor::crearThreadServer(){
	pthread_t thread_id;
	if( pthread_create( &thread_id , NULL , Servidor::actualizarModeloWrapper , this)  < 0)
		controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo crear el hilo del servidor");

 }

 void* Servidor::actualizarModeloWrapper(void *args){
	 Servidor* serv = (Servidor * )args;
 	 return serv->actualizarModelo();
}



  void *Servidor::actualizarModelo(){
	  juego = new Juego();
	  juego->crearJugador("Venom", 1);
	  juego->crearJugador("Spiderman", 2);
	  juego->crearJugador("Venom", 3);
	  juego->crearJugador("Venom", 4);
	  juego->crearEquipos();
	  Uint32 tiempoInicial,tiempoActual;
	  int FPS = controladorJson->cantidadFPS();

	  while(true){
		tiempoInicial= SDL_GetTicks();
		server_mutex.lock();
		this->dibujables = juego->dibujar();
		server_mutex.unlock();

		for(int i=0;i<clientesConectados.size();i++){
			enviarParaDibujar(clientesConectados[i],dibujables);
		}

		tiempoActual = SDL_GetTicks();
		 if(tiempoActual - tiempoInicial < 1000/FPS)
			SDL_Delay( 1000/FPS - tiempoActual +tiempoInicial );

	  }


 	return NULL;
  }

void Servidor::crearSocket(int puerto){
   socketServidor = socket(AF_INET , SOCK_STREAM , 0);
	if (socketServidor == -1)
		controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo crear el socket .");
	else
		controladorLogger->registrarEvento("INFO", "Servidor::Socket creado.");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( puerto );

	if( bind(socketServidor,(struct sockaddr *)&server , sizeof(server)) < 0)
		perror("enlace fallido. Error");
}

void Servidor::esperarConexiones(){
	iServidor* args = (iServidor*) malloc(sizeof(infoServidor));
	args->servidor=this;
	listen(socketServidor , 3);
	puts("Esperando conexiones...");
	int c = sizeof(struct sockaddr_in);
	pthread_t thread_recibir;

	while( true){
		socketCliente = accept(socketServidor, (struct sockaddr *)&client, (socklen_t*)&c);
		cantidad_actual_clientes++;
		this->sistemaEnvio.enviarEntero(cantidad_actual_clientes,socketCliente);
		 if (socketCliente < 0)
			 controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo aceptar la conexion .");
		args->csocket=socketCliente;
		puts("Conexion aceptada");

		if( pthread_create( &thread_recibir , NULL , Servidor::recibirTeclasWrapper , (void*) args)  < 0)
			controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo crear el hilo .");
		clientesConectados.push_back(socketCliente);
		cout<<"Bienvenido jugador "+to_string(cantidad_actual_clientes)<<endl;

	}
	free(args);
}

void *Servidor::recibirTeclasWrapper(void *args){
	iServidor* argumentos = (iServidor*) args;
	((Servidor *)argumentos->servidor)->recibirTeclas(argumentos->csocket);
	return NULL;
}

void Servidor::enviarParaDibujar(int socket,vector<tuple<string,SDL_Rect , SDL_Rect ,SDL_RendererFlip>> dibujablesThread){
	char textura[MAXDATOS];
	SDL_Rect rectOrigen;
	SDL_Rect rectDestino;
	SDL_RendererFlip flip;

	for(int i=0;i<dibujablesThread.size();i++){
			strcpy(textura,  get<0>(dibujablesThread[i]).c_str());
			rectOrigen =get<1>(dibujablesThread[i]);
			rectDestino =get<2>(dibujablesThread[i]);
			int posiciones[8]={rectOrigen.x,rectOrigen.y,rectOrigen.w,rectOrigen.h,rectDestino.x,rectDestino.y,rectDestino.w,rectDestino.h};
			flip = get<3>(dibujablesThread[i]);

			send(socket,textura,MAXDATOS,0);
			send(socket,posiciones,sizeof(posiciones),0);
			send(socket,&flip,sizeof(flip),0);
		}

} 

void Servidor::recibirTeclas(int csocket){
	SDL_Event evento;
	while(true){
		int tipoTeclado=this->sistemaEnvio.recibirEntero(csocket);
		recv(csocket,&evento,sizeof(evento),0);
		mutex juegoMutex;
		juegoMutex.lock();
		juego->teclear(evento,tipoTeclado);
		juegoMutex.unlock();
	}
}




