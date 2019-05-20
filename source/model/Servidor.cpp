#include <Servidor.hpp>
#include <vector>
#include <tuple>
#include <string>


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
	cantidadClientesPermitidos = controladorJson->cantidadClientes();
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
	  menu = new GameMenu();
	  Uint32 tiempoInicial,tiempoActual;
	  int FPS = controladorJson->cantidadFPS();

	/*  while (this->clientesConectados.size() < this->cantidadClientesPermitidos){
		  controladorLogger->registrarEvento("INFO", "Servidor:: Esperando Jugadores. Actualmente hay: " + to_string(clientesConectados.size()) + "/" + to_string(this->cantidadClientesPermitidos));
	  }*/

	  while(enMenu){
		  tiempoInicial= SDL_GetTicks();
		  server_mutex.lock();
		  this->dibujables = menu->getDibujables();
		  server_mutex.unlock();
		  for(size_t i=0;i<clientesConectados.size();i++){
				enviarParaDibujar(clientesConectados[i],dibujables);
			}
			tiempoActual = SDL_GetTicks();
			if(tiempoActual - tiempoInicial < 1000/FPS)
				SDL_Delay( 1000/FPS - tiempoActual +tiempoInicial );
			enMenu = !menu->finalizado();
	  }

	  map<int, string> personajesElegidos=menu->getPersonajesElegidos();
	  for(size_t i=0;i<personajesElegidos.size();i++){
		  string nombrePersonaje = personajesElegidos[i+1];
		  juego->crearJugador(nombrePersonaje, i+1);
	  }


	  juego->crearEquipos();

	  while(true){
		tiempoInicial= SDL_GetTicks();
		server_mutex.lock();
		this->dibujables = juego->dibujar();
		server_mutex.unlock();
		for(size_t i=0;i<clientesConectados.size();i++){
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
	cout << "Esperando conexiones. Faltan " << to_string(cantidadClientesPermitidos) << " clientes" << endl;
	int c = sizeof(struct sockaddr_in);
	pthread_t thread_recibir;
	while( true){
		socketCliente = accept(socketServidor, (struct sockaddr *)&client, (socklen_t*)&c);
		 if (socketCliente < 0)
			controladorLogger->registrarEvento("ERROR", "Servidor::No se pudo aceptar la conexion .");
		 else
			 controladorLogger->registrarEvento("INFO", "Servidor::Se acepto la conexion correctamente.");
		 if(clientesConectados.size()>=cantidadClientesPermitidos){
			 this->sistemaEnvio.enviarEntero(-1,socketCliente);
			 continue;
		 }

		clientesConectados.push_back(socketCliente);
		this->sistemaEnvio.enviarEntero(clientesConectados.size(),socketCliente);
		this->enviarTitulos(socketCliente);
		args->csocket=socketCliente;

		pthread_create( &thread_recibir , NULL , Servidor::recibirTeclasWrapper , (void*) args);

		cout<<"Bienvenido jugador "+to_string(clientesConectados.size()) << ". ";
		if (cantidadClientesPermitidos - clientesConectados.size() == 0)
			cout << "La partida esta llena. No se aceptaran mas jugadores." << endl;
		else
			cout << "Falta(n) " << to_string(cantidadClientesPermitidos - clientesConectados.size()) << " jugador(es)" << endl;

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
	int size = dibujablesThread.size();
	send(socket,&size,sizeof(int),0);
	for(size_t i=0;i<size;i++){
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


void Servidor::enviarTitulos(int csocket){
	vector<tuple<string,string,int,string,int ,int ,int >>titulos = this->menu->getTitulos(clientesConectados.size());
	char nombre[MAXDATOS];
	char path[MAXDATOS];
	int size;
	char descripcion[MAXDATOS];
	int r,g,b;
	for(size_t i=0;i<titulos.size();i++){
		strcpy(nombre,  get<0>(titulos[i]).c_str());
		strcpy(path,  get<1>(titulos[i]).c_str());
		size = get<2>(titulos[i]);
		strcpy(descripcion,  get<3>(titulos[i]).c_str());
		r = get<4>(titulos[i]);
		g = get<5>(titulos[i]);
		b = get<6>(titulos[i]);
		send(csocket,nombre,MAXDATOS,MSG_WAITALL);
		send(csocket,path,MAXDATOS,MSG_WAITALL);
		send(csocket,&size,sizeof(size),MSG_WAITALL);
		send(csocket,descripcion,MAXDATOS,MSG_WAITALL);
		send(csocket,&r,sizeof(r),MSG_WAITALL);
		send(csocket,&g,sizeof(g),MSG_WAITALL);
		send(csocket,&b,sizeof(b),MSG_WAITALL);
	}
}

void Servidor::recibirTeclas(int csocket){
	SDL_Event evento;
	while(true){
		int idCliente=this->sistemaEnvio.recibirEntero(csocket);
		if(recv(csocket,&evento,sizeof(evento),0)==0){
			controladorLogger->registrarEvento("INFO", "Servidor::Se desconecto el cliente "+to_string(csocket));
			for(size_t i=0;i<clientesConectados.size();i++){
				if(clientesConectados[i]==csocket)
					clientesConectados.erase(clientesConectados.begin()+i);
			}
			clientesDesconectados.push_back(csocket);
			return;
		}
		mutex juegoMutex;
		juegoMutex.lock();
		if(enMenu)
			menu->handleEvent(evento,idCliente);
		else
			juego->teclear(evento,idCliente);
		juegoMutex.unlock();
	}
}



