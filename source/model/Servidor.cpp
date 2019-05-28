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

void Servidor::esperarClientes(){
	controladorLogger->registrarEvento("DEBUG", "Servidor:: Esperando Jugadores. Actualmente hay: " + to_string(clientesConectados.size()) + "/" + to_string(this->cantidadClientesPermitidos));
	while (this->clientesConectados.size() < this->cantidadClientesPermitidos){

	}
}

void Servidor::correrMenu(){
	Uint32 tiempoInicial,tiempoActual;
	int FPS = controladorJson->cantidadFPS();

	while(enMenu){
		server_mutex.lock();
		tiempoInicial= SDL_GetTicks();
		this->dibujables = menu->getDibujables();
		tiempoActual = SDL_GetTicks();
		server_mutex.unlock();

		if(tiempoActual - tiempoInicial < 1000/FPS)
			SDL_Delay( 1000/FPS - tiempoActual +tiempoInicial );
		enMenu = !menu->finalizado();
		}
}

void Servidor::crearEquipos(){
	mutex crear_mutex;
	crear_mutex.lock();
	map<int, string> personajesElegidos = menu->getPersonajesElegidos();
	bool equipo1formado = false;
	for(size_t i=1;i<this->cantidadClientesPermitidos+1;i++){
	  string nombrePersonaje = personajesElegidos[i];
	  juego->crearJugador(nombrePersonaje, i);
	  if(this->cantidadClientesPermitidos == 1 ){
		  nombrePersonaje = personajesElegidos[i+1];
		  juego->crearJugador(nombrePersonaje, i+1);
		  nombrePersonaje = personajesElegidos[i+2];
		  juego->crearJugador(nombrePersonaje, i+2);
		  nombrePersonaje = personajesElegidos[i+3];
		  juego->crearJugador(nombrePersonaje, i+3);
	  }
	  if(this->cantidadClientesPermitidos == 2 ){
		  nombrePersonaje = personajesElegidos[i+10];
		  juego->crearJugador(nombrePersonaje, i+10);
	  }if(this->cantidadClientesPermitidos == 3 && not equipo1formado){
		  nombrePersonaje = personajesElegidos[i+10];
		  juego->crearJugador(nombrePersonaje, i+10);
		  equipo1formado = true;
	  }
	}
	juego->crearEquipos();
	if(this->cantidadClientesPermitidos == 2 || this->cantidadClientesPermitidos == 1){
		juego->getEquipo1()->habilitarTeclado();
		juego->getEquipo2()->habilitarTeclado();
	}
	if(this->cantidadClientesPermitidos == 3){
		juego->getEquipo1()->habilitarTeclado();
	}
	for(size_t i=0;i<clientesConectados.size();i++){
	  int finalizoMenu=-1;
	  send(clientesConectados[i],&finalizoMenu,sizeof(int),MSG_WAITALL);
	}
	crear_mutex.unlock();
}

void Servidor::gameLoop(){
	Uint32 tiempoInicial,tiempoActual;
	int FPS = controladorJson->cantidadFPS();

	while(true){

		tiempoInicial= SDL_GetTicks();

		server_mutex.lock();
		this->dibujables = juego->dibujar();
		server_mutex.unlock();

		tiempoActual = SDL_GetTicks();

		 if(tiempoActual - tiempoInicial < 1000/FPS)
			SDL_Delay( 1000/FPS - tiempoActual +tiempoInicial );

		}
}

void *Servidor::actualizarModelo(){
	this->juego = new Juego();
	this->menu = new GameMenu();
	Uint32 tiempoInicial,tiempoActual;
	int FPS = controladorJson->cantidadFPS();

	//this->esperarClientes();

	this->correrMenu();

	this->crearEquipos();

	this->gameLoop();

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
	cout<<"Servidor iniciado."<<endl;
	cout << "Esperando conexiones."<<endl;
	cout<<"Faltan " << to_string(cantidadClientesPermitidos) << " clientes." << endl;
	int c = sizeof(struct sockaddr_in);
	pthread_t thread_recibir,thread_enviar;

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
		conectados[socketCliente] =true;
		mapaIDClientes[socketCliente]= clientesConectados.size();
		this->sistemaEnvio.enviarEntero(clientesConectados.size(),socketCliente);
		this->enviarTitulos(socketCliente);
		args->csocket=socketCliente;
		pthread_create( &thread_enviar , NULL , Servidor::enviarWrapper , (void*) args);
		pthread_create( &thread_recibir , NULL , Servidor::recibirTeclasWrapper , (void*) args);
		cout<<"Bienvenido jugador "+to_string(clientesConectados.size()) << ". "<<endl;
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

void *Servidor::enviarWrapper(void *args){
	iServidor* argumentos = (iServidor*) args;
	((Servidor *)argumentos->servidor)->enviarParaDibujar(argumentos->csocket);
	return NULL;
}

void Servidor::enviarParaDibujar(int socket){
	Uint32 tiempoInicial,tiempoActual;
	vector<tuple<string,SDL_Rect , SDL_Rect ,SDL_RendererFlip>> dibujablesThread;

	while(true){
		if(!conectados[socket])
			continue;

		char textura[1000];
		SDL_Rect rectOrigen;
		SDL_Rect rectDestino;
		SDL_RendererFlip flip;

		tiempoInicial= SDL_GetTicks();

		server_mutex.lock();
		dibujablesThread=this->dibujables;
		server_mutex.unlock();

		int size = dibujablesThread.size();

		send(socket,&size,sizeof(int),0);
		for(size_t i=0;i<size;i++){
				strcpy(textura,  get<0>(dibujablesThread[i]).c_str());
				rectOrigen =get<1>(dibujablesThread[i]);
				rectDestino =get<2>(dibujablesThread[i]);
				int posiciones[8]={rectOrigen.x,rectOrigen.y,rectOrigen.w,rectOrigen.h,rectDestino.x,rectDestino.y,rectDestino.w,rectDestino.h};
				flip = get<3>(dibujablesThread[i]);

				send(socket,textura,1000,0);
				send(socket,posiciones,sizeof(posiciones),0);
				send(socket,&flip,sizeof(flip),0);
		}


		tiempoActual = SDL_GetTicks();
		 if(tiempoActual - tiempoInicial < 1000/60)
			SDL_Delay( 1000/60 - tiempoActual +tiempoInicial );

	}
}

void Servidor::enviarTitulos(int csocket){
	vector<tuple<string,string,int,string,int ,int ,int >>titulos = this->menu->getTitulos(clientesConectados.size());
	char nombre[MAXDATOS];
	char path[MAXDATOS];
	int size;
	char descripcion[MAXDATOS];
	int r,g,b;
	int cantidadTitulos = titulos.size();
	send(csocket,&cantidadTitulos,sizeof(int),0);
	for(size_t i=0;i<cantidadTitulos;i++){
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
	struct timeval tv = {1, 0};
	setsockopt(csocket, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv, sizeof(struct timeval));
	SDL_Event evento;
	int idCliente=mapaIDClientes[csocket];
	recv(csocket,&evento,sizeof(evento),MSG_WAITALL);
	while(true){
		int numBytes = recv(csocket,&evento,sizeof(evento),MSG_WAITALL);
		if(numBytes==0){
			juego->actualizarConexion(idCliente);
			cout<<"Se desconecto el cliente "+to_string(idCliente)<<endl;
			controladorLogger->registrarEvento("INFO", "Servidor::Se desconecto el cliente "+to_string(idCliente));
			conectados[csocket] =false;
			return;
		}
		if(numBytes<0){
			if(conectados[csocket] && !enMenu){
				juego->actualizarConexion(idCliente);
				conectados[csocket] =false;
				cout<<"Se desconecto el cliente "<<idCliente<<endl;
			}
			continue;
		}
		if(!conectados[csocket]){
			cout<<"Se reconecto el cliente "<<idCliente<<endl;
			conectados[csocket]=true;
			juego->actualizarConexion(idCliente);
		}

		if(evento.type==SDL_MOUSEWHEEL)//descarto el heartbeat
			continue;
		server_mutex.lock();
		if(enMenu)
			menu->handleEvent(evento,idCliente);
		else
			juego->teclear(evento,idCliente);
		server_mutex.unlock();
	}
}




